let log = a => {
  Js.log(a);
  a;
};

let debugList = list => {
  let array = Array.of_list(list);
  Js.log(array);
  list;
};