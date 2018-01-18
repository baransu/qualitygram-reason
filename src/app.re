[@bs.module] external logo : string = "./logo.svg";

let text = ReasonReact.stringToElement;

let api = "https://jsonplaceholder.typicode.com";

let makeRequest = (callback) => Js.Promise.(
  Fetch.fetch(api ++ "/posts/1")
  |> then_(Fetch.Response.json)
  |> then_(text => callback(text) |> resolve)
);

type action = Increase | Decrease;
type state = int;

/* Why this have to be after the action and state - I don't know and understand */
let component = ReasonReact.reducerComponent("App");

let make = (_children) => { 
  ...component,

  initialState: () => 0,

  reducer: (action, state) => 
    switch(action) {
    | Increase => ReasonReact.Update(state + 1)
    | Decrease => ReasonReact.Update(state - 1)
    },

  render: (self) => {
    let count = "Counter: " ++ string_of_int(self.state);
    let increase = (_event) => {
      makeRequest((_) => {
        self.send(Increase);
      }) |> ignore;
    };

    <div>(text(count))
      <button onClick=increase>(text("+"))</button>
      <button onClick={(_) => self.send(Decrease)}>(text("-"))</button>
    </div>
  }
};
