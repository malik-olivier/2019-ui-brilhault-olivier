type page = 
    | Register
    | Login;

module App = {
    type state = {route: page};
    type action =
        | UpdatePage(page);
    let component = ReasonReact.reducerComponent("App");
    let make = _children => {
        ...component, 
        initialState: () => {route: Register},
        didMount: self => {
            let watcherID =
              ReasonReact.Router.watchUrl(url =>
                switch (url.path) {
                | ["login"] => self.send(UpdatePage(Login))
                | _ => self.send(UpdatePage(Register))
                }
              );
              self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
          },
        reducer: (action, _state) =>
            switch (action) {
            | UpdatePage(route) => ReasonReact.Update({route: route})
            },
        
        render: ({state}) =>
        <div>(
          switch (state.route) {
          | Register => <Register />
          | Login => <Login />
          }
        )</div>
    };
  };

  ReactDOMRe.renderToElementWithId(<App />, "main");
