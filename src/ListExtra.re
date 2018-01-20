let includes = (pattern: string, list: list(string)) : bool =>
  List.exists(StringExtra.equal(pattern), list);

let lengthToString = list => list |> List.length |> string_of_int;