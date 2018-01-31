type result('a, 'b) =
  | Ok('a)
  | Err('b);

/* Make task - returns new task */
let success = a => Js.Promise.resolve(Ok(a));

let fail = a => Js.Promise.resolve(Err(a));

let andThen = (fn, task) =>
  Js.Promise.then_(
    a =>
      switch a {
      | Ok(a) => fn(a)
      | Err(e) => fail(e)
      },
    task
  );

let onError = (fn, task) =>
  Js.Promise.then_(
    a =>
      switch a {
      | Err(a) => fn(a)
      | Ok(a) => success(a)
      },
    task
  );

let map = (fn, task) => task |> andThen(a => success(fn(a)));

let map2 = (fn, taskA, taskB) =>
  taskA |> andThen(a => taskB |> andThen(b => success(fn(a, b))));

let mapError = (fn, task) => task |> onError(e => fail(fn(e)));

let rec sequence = list =>
  switch list {
  | [] => success([])
  | [task, ...remainingTasks] => map2((a, b) => [a, ...b], task, sequence(remainingTasks))
  };