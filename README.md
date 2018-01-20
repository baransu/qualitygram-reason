# qualitygram-reason

Qualitygram written in Reason.

## Learning resources

List of links to best resources to learn about Reason, it's features and quirks.

* https://reasonml.github.io
* https://reasonml.github.io/reason-react/
* http://2ality.com/2017/11/about-reasonml.html

## Problems

My problems with Reason before any serious usage in production code. Divided in three levels of complexity how to solve them.

### Easy:

* Some problems with Promises and Fetch API. It can be a lot better not only in terms of better code (or batter naming), but also in terms of better documentation. Not clear and no examples how to handle errors properly.
* Not polished Promise API. `then_` works differently than in JS while we're expecting it to work the same. (https://github.com/BuckleScript/bucklescript/issues/1739, https://github.com/BuckleScript/bucklescript/pull/2046)
* I have a problems with compilation and error messages ~and formatting~. ~I don't know why it's not working propertly for me. I have all required tools installed and available through terminal but in editor (VSCode), it's not working as intended.~ Project setup was done using `create-react-app` with `reason-scripts@0.8.0`. For some reason (no pun intended) error messages are broken for me, e.g:
  ![Example error 1](/assets/error_1.png)
  I'm expecting that it's an easy fix but it's causing a lot of headache right now.
* List and String modules are not what I've expected. I was expecting more Elm/JS mix with some utils like String equality check that returns true.
* `Js.Log` returns `unit` so you cannot add it easly to pipe: `a |> List.map(a => b) |> Js.log |> Array.of_list`.

### Medium:

### Hard:
