let classnames = (classes: list((string, bool))) =>
  List.fold_left(
    (acc, item) =>
      switch item {
      | (className, true) => acc ++ " " ++ className
      | (_, false) => acc
      },
    "",
    classes
  );