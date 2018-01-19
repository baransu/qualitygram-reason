type profile = {
  username: string,
  profilePicture: string
};

type action =
 | Fetch
 | AddProfile(profile);

type state = {
  processed: list(string),
  queue: list(string),
  profiles: list(profile),
  images: list(string)
};


let decodeProfile = json => Json.Decode.{
  username: json |> field("user", field("username", string)),
  profilePicture: json |> field("user", field("profile_pic_url_hd", string))
};

let fetchMore = (self) => {
  List.map(
    username => Api.getUser(username)
    |> Promise.andThen(decodeProfile)
    |> Promise.andThen(profile => {
      self.send(AddProfile(profile))
    })
    |> ignore,
    self.state.queue
  ) |> ignore
};

/* Why this have to be after the action and state - I don't know and understand */
let component = ReasonReact.reducerComponent("App");

let initialState = () => { 
  processed: [], 
  queue: ["instagram"],
  profiles: [],
  images: []
};

/**
 * It's cool that reducer can be just a function like anything else so 
 * we can have some space or we can even move logic into separe file
 */
let reducer = (action, state) =>
  switch(action) {
  | Fetch => ReasonReact.SideEffects(self => fetchMore(self.state, self.send))
  | AddProfile(profile) => {
      ReasonReact.Update({
        ...state,
        profiles: [profile, ...state.profiles]
      })
    }
  };

let make = (_children) => { 
  ...component,

  initialState,
  reducer,
  render: (self) => {
    let count = "Processed: " ++ 
      (self.state.processed |> List.length |> string_of_int); /* ++ string_of_int(self.state);*/

    <div>
      <h1>
        (Html.text(count))
      </h1>
      <div>
        (Html.map(user => Html.text(user.username), self.state.profiles))
      </div>
      <button onClick={(_) => self.send(Fetch)}>(Html.text("fetch"))</button>
    </div>
  }
};