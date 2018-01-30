/**
 * Our types
 */
type image = {
  id: string,
  src: string
};

type action =
  | ProcessQueue
  | ProcessResult(list(string), list(image))
  | Error;

type state = {
  error: option(string),
  loading: bool,
  processed: list(string),
  queue: list(string),
  images: list(image)
};

/**
 * Set of decoders to decode instagram responses
 */
module Decode = {
  let codes = json =>
    Json.Decode.(
      json
      |> field("user") @@
      field("media") @@
      field("nodes") @@
      array @@
      field("code") @@
      string
    );
  let media = (json, decoder) =>
    Json.Decode.(
      json |> field("graphql") @@ field("shortcode_media") @@ decoder
    );
  let image = json => {
    let media = media(json);
    Json.Decode.{
      id: media @@ field("id") @@ string,
      src: media @@ field("display_url") @@ string
    };
  };
  let usernames = json => {
    let media = media(json);
    let edges = decoder =>
      Json.Decode.(field("edges") @@ array @@ field("node") @@ decoder);
    let likes =
      Json.Decode.(
        media @@
        field("edge_media_preview_like") @@
        edges @@
        field("username") @@
        string
      )
      |> Array.to_list;
    /* |> Debug.log; */
    let comments =
      Json.Decode.(
        media @@
        field("edge_media_to_comment") @@
        edges @@
        field("owner") @@
        field("username") @@
        string
      )
      |> Array.to_list;
    /* |> Debug.log; */
    List.flatten([likes, comments]);
  };
};

/**
 * Fetching profile,
 * getting codes
 * mapping codes to image details
 * decoding them and adding to state
 */
let fetchProfile = (username, send) =>
  Api.getUser(username)
  |> Promise.then_(profile =>
       profile
       |> Decode.codes
       |> Array.map(Api.getImage(username))
       |> Promise.all
     )
  |> Promise.andThen(images => {
       let usernames =
         images |> Array.to_list |> List.map(Decode.usernames) |> List.flatten;
       let images = images |> Array.map(Decode.image) |> Array.to_list;
       let u = ListExtra.lengthToString(usernames);
       let i = ListExtra.lengthToString(images);
       Js.log(
         username ++ ": found " ++ u ++ " usernames and " ++ i ++ " images!"
       );
       send(ProcessResult(usernames, images));
       ();
     })
  |> Promise.catch((_) => {
       send(Error);
       Promise.resolve();
     })
  |> ignore;

/**
 * It's cool that reducer can be just a function like anything else so
 * we can have some space or we can even move logic into separe file
 */
let reducer = (action, state) =>
  switch action {
  | Error =>
    ReasonReact.Update({...state, error: Some("Something went wrong")})
  | ProcessQueue =>
    if (List.length(state.processed) < 20) {
      switch state.queue {
      | [] => ReasonReact.NoUpdate
      | [head, ...queue] =>
        ReasonReact.UpdateWithSideEffects(
          {
            ...state,
            queue,
            processed: [head, ...state.processed],
            loading: true
          },
          (self => fetchProfile(head |> Debug.log, self.send))
        )
      };
    } else {
      Js.log("Finished!");
      ReasonReact.NoUpdate;
    }
  | ProcessResult(usernames, images) =>
    let queue =
      List.fold_left(
        (acc, a) =>
          if (! ListExtra.includes(a, acc)
              && ! ListExtra.includes(a, state.processed)) {
            [a, ...acc];
          } else {
            acc;
          },
        state.queue,
        usernames
      );
    ReasonReact.UpdateWithSideEffects(
      {
        ...state,
        queue,
        images: List.append(List.rev(images), state.images),
        loading: false
      },
      (self => self.send(ProcessQueue))
    );
  };

let make = _children => {
  ...ReasonReact.reducerComponent("App"),
  initialState: () => {
    error: None,
    loading: false,
    processed: [],
    queue: ["instagram"],
    images: []
  },
  reducer,
  render: ({state, send}) => {
    let loader =
      if (state.loading) {
        <Button onClick=((_) => send(ProcessQueue)) primary=false>
          (Html.text("Loading..."))
        </Button>;
      } else if (List.length(state.queue) > 0) {
        <Button onClick=((_) => send(ProcessQueue)) primary=true>
          (Html.text("fetch"))
        </Button>;
      } else {
        ReasonReact.nullElement;
      };
    let error =
      switch state.error {
      | Some(e) => Html.text(e)
      | None => ReasonReact.nullElement
      };
    <div>
      <h1>
        (Html.text("Images: " ++ ListExtra.lengthToString(state.images)))
      </h1>
      <h1>
        (Html.text("Processed: " ++ ListExtra.lengthToString(state.processed)))
      </h1>
      <h1>
        (Html.text("Queue: " ++ ListExtra.lengthToString(state.queue)))
      </h1>
      (error)
      (loader)
      <div>
        (
          state.images
          |> List.rev
          |> Html.map(i => <img key=i.id height="650" width="650" src=i.src />)
        )
      </div>
    </div>;
  }
};