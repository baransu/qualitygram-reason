/* TODO: understand how to handle errors */
exception SieWyjebalo;

let get = (path: string) =>
  Fetch.fetch(path)
  |> Promise.then_(res => res |> Fetch.Response.json)
  |> Promise.catch(err => {
       Js.log(err);
       Promise.reject(SieWyjebalo);
     });

let getUser = (user: string) => get("/api/users/" ++ user);

let getImage = (user: string, code: string) =>
  get("/api/users/" ++ user ++ "/" ++ code);