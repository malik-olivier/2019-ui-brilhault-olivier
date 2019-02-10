module App = {
  type state = {
    path: string,
    hash: string,
  };

  type action =
    | RedirectToLogin
    | RedirectToRegister;

  let component = ReasonReact.reducerComponent("App");

  let make = _children => {
    ...component,
    reducer: (action, state) =>
      switch (action) {
      /* router actions */
      | RedirectToLogin => ReasonReact.Update({...state, path: "http://localhost:1234/login"})
      | RedirectToRegister => ReasonReact.Update({...state, path: "http://localhost:1234/register"})
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

//ReactDOMRe.renderToElementWithId(<App />, "main");
