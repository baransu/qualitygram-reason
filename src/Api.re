/* TODO: understand how to handle errors */
exception SieWyjebalo;

let get = (path: string) =>
  Fetch.fetch(path)
  |> Js.Promise.then_(res => res |> Fetch.Response.json)
  |> Js.Promise.then_(res => res |> Task.success)
  |> Js.Promise.catch(err => {
       Js.log(err);
       Task.fail("sie wyjebalo");
     });

let getUser = (user: string) => get({j|/api/users/$user|j});

let getImage = (user: string, code: string) =>
  get({j|/api/users/$user/$code|j});