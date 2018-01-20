let resolve = Js.Promise.resolve;

let reject = Js.Promise.reject;

let catch = Js.Promise.catch;

let all = Js.Promise.all;

let then_ = Js.Promise.then_;

let andThen = (fn, promise) =>
  Js.Promise.then_(a => fn(a) |> Js.Promise.resolve, promise);