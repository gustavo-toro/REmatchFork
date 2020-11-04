import React, { Component } from 'react';

import Paper from '@material-ui/core/Paper';
import Divider from '@material-ui/core/Divider';
import Button from '@material-ui/core/Button';

import PlayArrow from '@material-ui/icons/PlayArrow';

import CodeMirror from 'codemirror';

class Viewer extends Component {
  constructor(props) {
    super(props);
    this.state = {
      idx: props.idx,
      text: props.text,
      // If regex is used
      regex: props.regex,
      // If rematch is used
      worker: props.worker,
      rematch: props.rematch,
    }
  }

  createEditor(type) {
    return CodeMirror(document.getElementById(`${type}Editor-${this.props.idx}`), {
      value: this.state[type],
      mode: (type === 'rematch') ? 'REmatchQuery' : (type === 'regex') ? 'RegExQuery' : null,
      theme: 'material-darker',
      lineNumbers: false,
      scrollbarStyle: null,
      smartIndent: false,
      indentWithTabs: true,
      undoDepth: 100,
      viewportMargin: 10,
      lineNumbers: (type === 'text'),
      lineWrapping: (type === 'text'),
      //readOnly: 'nocursor',
    })
  }

  componentDidMount() {
    let textEditor = this.createEditor('text');
    this.setState({ textEditor });
    if (this.props.rematch) {
      let rematchEditor = this.createEditor('rematch');
      this.setState({ rematchEditor });
    }
    if (this.props.regex) {
      let regexEditor = this.createEditor('regex');
      this.setState({ regexEditor });
    }
  }

  render() {
    return (
      <Paper className="viewerPaper" elevation={3}>
        <div className="textEditor" id={`textEditor-${this.props.idx}`}></div>
        <Divider />
        <div className="queryContainer">
          {(this.state.rematch) ?
            <div className="queryEditor" id={`rematchEditor-${this.props.idx}`}></div>
            : null}
          {(this.state.rematch && this.state.regex) ?
            <Divider orientation="vertical" flexItem />
            : null}
          {(this.state.regex) ?
            <div className="queryEditor" id={`regexEditor-${this.props.idx}`}></div>
            : null}
          {!(this.state.rematch && this.state.regex) ?
            <Button
              className="button"
              color={this.state.rematch ? 'primary' : 'secondary'}
              startIcon={<PlayArrow />}
              size="small">
              {(this.state.rematch) ? 'REmatch' : 'RegEx'}
            </Button>
            : null}
        </div>
        <Divider />
        {(this.state.rematch && this.state.regex) ?
          <>
            <div className="buttonContainer">
              <Button
                className="button"
                color="primary"
                startIcon={<PlayArrow />}
                size="small">
                REmatch
              </Button>
              <Divider orientation="vertical" flexItem />
              <Button
                className="button"
                color="secondary"
                startIcon={<PlayArrow />}
                size="small">
                RegEx
              </Button>
            </div>
            <Divider />
          </>
          : null}
        <div className="matchesContainer">
          {(this.state.rematch) ?
            <div className="matches">
              Match 1 REmatch blabla<br />
            Match 2 REmatch blabla<br />
            Match 3 REmatch blabla<br />
            </div>
            : null}
          {(this.state.rematch && this.state.regex) ?
            <Divider orientation="vertical" flexItem />
            : null}
          {(this.state.regex) ?
            <div className="matches">
              Match 1 RegEx blabla<br />
            Match 2 RegEx blabla<br />
            Match 3 RegEx blabla<br />
            </div>
            : null}
        </div>
      </Paper>
    )
  }
}

export default Viewer;