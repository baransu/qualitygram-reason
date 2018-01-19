
let get = (path: string) => 
  Fetch.fetch(path)
  |> Promise.then_(Fetch.Response.json);
  /* TODO: understand how to handle errors */
  

let getUser = (user: string) => get("/api/users/" ++ user);

let getImage = (code: string, user: string) => get("/api/users/" ++ user ++ "/" ++ code);
