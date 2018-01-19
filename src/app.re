/**
 * Our type
 */
type image = {
  id: string,
  src: string
};

type action =
 | ProcessQueue
 | AddImages(list(image));

type state = {
  loading: bool,
  processed: list(string),
  queue: list(string),
  images: list(image)
};

/**
 * Set of decoders to decode instagram responses
 */
module Decode {
  let codes = json => Json.Decode.(
    json |> field("user", field("media", field("nodes", array(field("code", string)))))
  );

  let image = json => { 
    let media = (decoder) => Json.Decode.(json |> field("graphql", field("shortcode_media", decoder)));
    Json.Decode.{
      id: media(field("id", string)),
      src: media(field("display_url", string))
    }
  };
};

/**
 * Fetching profile,
 * getting codes
 * mapping codes to image details
 * decoding them and adding to state
 */
let fetchProfile = (username, send) => {
  Api.getUser(username)
    |> Promise.then_(profile => 
        profile
        |> Decode.codes
        |> Array.map(Api.getImage(username)) 
        |> Promise.all
    )
    |> Promise.andThen(images => 
        images 
        |> Array.map(Decode.image) 
        |> Array.to_list 
        |> (s => AddImages(s))
        |> send
    )
    |> ignore
};

/**
 * It's cool that reducer can be just a function like anything else so 
 * we can have some space or we can even move logic into separe file
 */
let reducer = (action, state) =>
  switch(action) {
  | ProcessQueue => {
    switch (state.queue) {
    | [] => ReasonReact.NoUpdate
    | [head, ...queue] => ReasonReact.UpdateWithSideEffects(
        { ...state, queue, loading: true },
        self => fetchProfile(head, self.send)
      )
    }
    
  }
  | AddImages(images) => {
      ReasonReact.UpdateWithSideEffects({
        ...state,
        loading: false,
        images: List.append(images, state.images)
      }, self => self.send(ProcessQueue))
    }
  };

let make = (_children) => { 
  ...ReasonReact.reducerComponent("App"),
  initialState: () => { 
    loading: false,
    processed: [], 
    queue: ["instagram"],
    images: []
  },
  reducer,
  render: (self) => {
    let queueLength = (self.state.queue |> List.length |> string_of_int);

    let loader = if (self.state.loading) {
      Html.text("Loading...")
    } else if (List.length(self.state.queue) > 0) {
      <button onClick={(_) => self.send(ProcessQueue)}>(Html.text("fetch"))</button>
    } else {
      <div/>
    };

    <div>
      <h1>
        (Html.text("In queue: " ++ queueLength))
      </h1>
      (loader)
      <div>
        (Html.map(i => <img key=i.id src=i.src />, self.state.images))
      </div>
    </div>
  }
};