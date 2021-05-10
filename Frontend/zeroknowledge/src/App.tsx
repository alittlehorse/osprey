import React, { Component } from 'react';
import { BrowserRouter as Router, Route, Link } from "react-router-dom";
import Header from './Home/Nav0';
import Footer from './Home/Footer1';
import Home from './Home';

import {
  Nav01DataSource,
  Footer10DataSource,
} from './Home/data.source.js';
import Code from './Components/Code/code';
import MyResult from './Components/Result/result';



class App extends Component {
  constructor(props: {} | Readonly<{}>) {
    super(props);
  }
  render() {
    return (
      <Router>
        <div>
          <Route exact path="/" component={Home} />
          <Route exact path="/code" component={Code} />
          <Route exact path="/result" component={MyResult} />
        </div>
      </Router>
    );
  }
}

export default App;