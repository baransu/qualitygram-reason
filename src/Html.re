/**
 * Collection of util functions to work with DOM
 */
/**
 * Changes string to DOM element
 */
let text = ReasonReact.stringToElement;

/**
 * Maps any list to array of DOM elements
 */
let map = (fn, collection) =>
  List.map(fn, collection) |> Array.of_list |> ReasonReact.arrayToElement;

let mapi = (fn, collection) =>
  List.mapi(fn, collection) |> Array.of_list |> ReasonReact.arrayToElement;