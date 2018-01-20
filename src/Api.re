/* TODO: understand how to handle errors */
let get = (path: string) =>
  Fetch.fetch(path) |> Promise.then_(Fetch.Response.json);

let getUser = (user: string) => get("/api/users/" ++ user);

let getImage = (user: string, code: string) =>
  get("/api/users/" ++ user ++ "/" ++ code);