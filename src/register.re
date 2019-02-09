type action =
  | UpdateEmail(string)
  | UpdateFirstName(string)
  | UpdateLastName(string)
  | UpdatePassword(string)
  | Register
  | RedirectToLogin;

type state = {
  email : string,
  password : string,
  firstname : string,
  lastname : string
};

let component = ReasonReact.reducerComponent("Register");

let make = _children => {
  ...component,
  initialState: () => {email: "",firstname: "" ,lastname: "",password: ""  },
  reducer: (action, state) =>
    switch action {
    | UpdateEmail(p) => ReasonReact.Update({...state,email: p})
    | UpdateFirstName(p) => ReasonReact.Update({...state,firstname : p})
    | UpdateLastName(p) => ReasonReact.Update({...state,lastname: p})
    | UpdatePassword(p) => ReasonReact.Update({...state,password : p})
    | Register => ReasonReact.Update({...state,password : state.password})
    | RedirectToLogin => ReasonReact.Update({...state,firstname : state.password})
    },
  render: self =>
    <div>
      <h1> (ReasonReact.string("Register for the best application")) </h1>
      <h2> (self.state.firstname |> ReasonReact.string) </h2>
      <div>
          <div>
            <span>(ReasonReact.string("FirstName : "))
              <input type_="text" onChange=((_evt) => self.send(UpdateFirstName(ReactEvent.Form.target(_evt)##value)))/>
            </span>
          </div>
          <div>
            <span>(ReasonReact.string("LastName : "))
              <input type_="text" onChange=((_evt) => self.send(UpdateLastName(ReactEvent.Form.target(_evt)##value)))/>
            </span>
          </div>
          <div>
            <span>(ReasonReact.string("Email : "))
              <input type_="email" onChange=((_evt) => self.send(UpdateEmail(ReactEvent.Form.target(_evt)##value)))/>
            </span>
          </div>
          <div>
            <span>(ReasonReact.string("Password : "))
              <input type_="password" onChange=((_evt) => self.send(UpdatePassword(ReactEvent.Form.target(_evt)##value)))/>
            </span>
          </div>
          <div>
            <button onClick=((_) => self.send(Register))>
              (ReasonReact.string("Register"))
            </button>
            <button onClick=((_) => self.send(RedirectToLogin))>
              (ReasonReact.string("Log in"))
            </button>
          </div>
        </div>
    </div>
};


