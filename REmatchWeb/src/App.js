import React from "react";
import {
  BrowserRouter as Router,
  Switch,
  Route,
} from "react-router-dom";

import { createMuiTheme, ThemeProvider } from '@material-ui/core/styles';
import CssBaseline from "@material-ui/core/CssBaseline";

import Navbar from './components/Navbar';
import AboutInterface from './components/AboutInterface';
import MainInterface from './components/Maininterface';

/* MATERIAL UI DARK THEME */
const darkTheme = createMuiTheme({
  palette: {
    type: 'dark',
    primary: {
      main: '#03DAC6',
    },
    secondary: {
      main: '#FCE938',
    },
    background: {
      paper: '#212121',
      default: '#424242',
    }
  },
});

const App = () => {
  return (
    <ThemeProvider theme={darkTheme}>
      <CssBaseline />
      <Router>
        <Navbar/>
        <Switch>
          <Route path="/about">
            <AboutInterface />
          </Route>
          <Route path="/">
            <MainInterface />
          </Route>
        </Switch>
      </Router>
    </ThemeProvider>
  )
}

export default App;