module App = {
  let component = ReasonReact.statelessComponent("App");

  type userStatus =
    | isAuthenticated
    | isNotAuthenticated;

  type state =
    | path: string
    | isUserLoggedIn: Bool;

  type action =
    | RedirectToLogin
    | RedirectToRegister;

  let make = _children => {
    ...component,
    reducer: (action, state) =>
      switch (action) {
      /* router actions */
      | RedirectToLogin => ReasonReact.Update({...state, nowShowing: AllTodos})
      | RedirectToRegister => ReasonReact.Update({...state, nowShowing: AllTodos})
      },
    didMount: self => {
      let watcherID =
        ReasonReact.Router.watchUrl(url =>
          switch (url.path) {
          | ["login"] => self.send(RedirectToLogin)
          | ["register"] => self.send(RedirectToRegister)
          | _ => self.send(RedirectToRegister)
          }
        );
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
    },
    render: _self => <Register />,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");
