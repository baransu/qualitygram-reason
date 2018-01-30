# qualitygram-reason

## Running application

We have both frontend application as well as backend proxy to instagram public API.
To run application run

```
yarn start
```

in one terminal and

```
yarn server
```

in other. You're application will be availabe at http://localhost:3000.

Qualitygram written in Reason.

## Learning resources

List of links to best resources to learn about Reason, it's features and quirks.

* https://reasonml.github.io
* https://reasonml.github.io/reason-react/
* http://2ality.com/2017/11/about-reasonml.html

## Problems

My problems with Reason before any serious usage in production code. Divided in three levels of complexity how to solve them.

### Easy:

* Some problems with Promises and Fetch API. It can be a lot better not only in terms of better code (or batter naming), but also in terms of better documentation. Not clear and no examples how to handle errors properly. Some good resources on Promises. General though is to not rely on `then`/`catch` mechanism as in JS and rather on `Js.Result.(Error/Ok)` which makes sense but is more problematic when chaining. Can be wrapped for better expecience. Subject to investigate.
* Not polished Promise API. `then_` works differently than in JS while we're expecting it to work the same. (https://github.com/BuckleScript/bucklescript/issues/1739, https://github.com/BuckleScript/bucklescript/pull/2046)
* I have a problems with compilation and error messages ~and formatting~. ~I don't know why it's not working propertly for me. I have all required tools installed and available through terminal but in editor (VSCode), it's not working as intended.~ Project setup was done using `create-react-app` with `reason-scripts@0.8.0`. For some reason (no pun intended) error messages are broken for me, e.g:
  ![Example error 1](/assets/error_1.png)
  I'm expecting that it's an easy fix but it's causing a lot of headache right now.
* List and String modules are not what I've expected. I was expecting more Elm/JS mix.
* `Js.Log` returns `unit` so you cannot add it easly to pipe: `a |> List.map(a => b) |> Js.log |> Array.of_list`.
* First if struggled because Reason does not have template strings so it's not easy to create bindins to `styled-components`. There is probably some way but I had no idea how to do this. Then I've tried `bs-glomor` but I wasn't that nice. My main problem was with lack of creating components with styles the same was as `styled-components` nad `glamorous` are doing. After writing some code that was and doing some research about other libraries I've found `bs-css` which is using `glamor` underneath. It works quite good and changing my approach from creating components into creating just styles/class names works quite well. Im waiting which CSS-in-JS approach Reason will support as they docs are teasing [here](https://reasonml.github.io/reason-react/docs/en/style.html#docsNav):
  > Since CSS-in-JS is all the rage right now, we'll recommend our official pick soon.

### Medium:

* TODO: write more about passing down props

### Hard:
