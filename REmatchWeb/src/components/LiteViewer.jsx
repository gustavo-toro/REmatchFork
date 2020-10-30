import React, { Component } from 'react';

import Paper from '@material-ui/core/Paper';
import Divider from '@material-ui/core/Divider';
import Button from '@material-ui/core/Button';
import Tabs from '@material-ui/core/Tabs';
import Tab from '@material-ui/core/Tab';

import PlayArrow from '@material-ui/icons/PlayArrow';

/* CodeMirror */
import CodeMirror from 'codemirror';
import 'codemirror/theme/material-darker.css';
import 'codemirror/addon/mode/simple';

CodeMirror.defineSimpleMode('REmatchQuery', {
  start: [
    {
      regex: /(![A-Za-z0-9]+\{|\})/,
      token: 'm0'
    },
    {
      regex: /(\\d)|(\\w)|(\\s)|(\\t)|(\\r)|(\\n)|(\\\()|(\\\))|(\\\[)|(\\\])|(\\\{)|(\\\})|(\\\.)|(\\-)|(\\_)/i,
      token: 'm2'
    },
    {
      regex: /(\(|\)|\||\[|\]|-)/,
      token: 'm3'
    },
    {
      regex: /(\.\+|\.\*|\.|\+)/,
      token: 'm1'
    },
    {
      regex: /<[0-9]+(,[0-9]+)?>/,
      token: 'm5'
    },
  ]
});

CodeMirror.defineSimpleMode('RegExQuery', {
  start: [
    {
      regex: /./,
      token: 'm0'
    },
  ]
});

class LiteViewer extends Component {
  constructor(props) {
    super(props);
    this.state = {
      rematch: props.rematch,
      regex: props.regex,
      text: props.text,
      idx: props.idx,
      idle: true,
      schema: [],
      rematchMatches: [],
      regexMatches: [],
      tab: 0,
      worker: props.worker,
    };
  }

  componentDidMount() {
    let queryEditor = CodeMirror(document.getElementById(`queryEditor-${this.props.idx}`), {
      value: (this.state.rematch) ? this.props.rematch : this.props.regex,
      mode: (this.state.rematch) ? 'REmatchQuery' : 'RegExQuery',
      theme: 'material-darker',
      lineNumbers: false,
      scrollbarStyle: null,
      smartIndent: false,
      indentWithTabs: true,
      undoDepth: 100,
      viewportMargin: 10,
      //readOnly: 'nocursor',
    });
    let textEditor = CodeMirror(document.getElementById(`textEditor-${this.props.idx}`), {
      value: this.state.text,
      mode: 'text/plain',
      theme: 'material-darker',
      lineNumbers: false,
      scrollbarStyle: 'native',
      smartIndent: false,
      indentWithTabs: true,
      undoDepth: 100,
      viewportMargin: 15,
      readOnly: 'nocursor',
      lineWrapping: true,
    });
    this.setState({ queryEditor, textEditor });
  }

  getText(span) {
    return this.state.textEditor.getRange(this.state.textEditor.posFromIndex(span[0]), this.state.textEditor.posFromIndex(span[1])).replaceAll(' ', '␣');
  }

  runRegEx() {
    this.setState({ regexMatches: this.state.textEditor.getValue().match(new RegExp(this.state.regex)) });
  }

  runREmatch() {
    this.state.worker.postMessage({
      text: this.state.textEditor.getValue(),
      query: this.state.rematch,
    });
    this.state.worker.onmessage = (m) => {
      switch (m.data.type) {
        case 'SCHEMA':
          this.setState({ schema: m.data.payload });
          break;
        case 'MATCHES':
          this.setState({ rematchMatches: m.data.payload });
          break;
        default:
          break;
      }
    }
  }

  handleRun() {
    if (this.state.rematch) {
      this.runREmatch();
    }
    if (this.state.regex) {
      this.runRegEx();
    }
    this.setState({ idle: false });
  }

  handleTabChange() {
    if (this.state.rematch && this.state.regex) {
      this.state.queryEditor.setOption('mode', (this.state.tab === 1) ? 'REmatchQuery' : 'RegExQuery');
      this.state.queryEditor.setValue((this.state.tab === 1) ? this.state.rematch : this.state.regex);
      this.setState(prevState => ({ tab: prevState.tab ^ 1 }));
    }
  }

  render() {
    return (
      <div>
        <Paper className="paperLite" elevation={3}>
          <Tabs
            value={this.state.tab}
            indicatorColor="primary"
            textColor="primary"
            onChange={this.handleTabChange.bind(this)}
            variant="fullWidth"
            disabled
          >
            {(this.state.rematch) ?
              <Tab label="REmatch" className="liteTab" style={{cursor: (this.state.regex) ? 'pointer' : 'default'}}/>
              : null}
            {(this.state.regex) ?
              <Tab label="RegEx" className="liteTab" style={{cursor: (this.state.rematch) ? 'pointer' : 'default'}}/>
              : null}
          </Tabs>
          <div className="queryContainer">
            <div className="queryEditor" id={`queryEditor-${this.props.idx}`}></div>
          </div>
          <Divider variant="middle" />
          <div className="textEditor" id={`textEditor-${this.props.idx}`}></div>
          <Divider variant="middle" />


          <div className="results">
            {
              (this.state.idle) ? (
                <div className="buttonContainer">
                  <Button
                    color="primary"
                    startIcon={<PlayArrow />}
                    onClick={this.handleRun.bind(this)}
                    size="large"
                  >
                    Run
                </Button>
                </div>) : (
                  <div className="list">
                    {(this.state.tab === 0 && this.state.rematch != null) ? (this.state.rematchMatches.map((match, idxMatch) => (
                      <div key={idxMatch} className="resultRow">
                        {Object.keys(match).map((variable, idxVariable) => (
                          <div key={idxVariable} className={`cm-m${idxVariable} resultItem`}>{variable}: {this.getText(match[variable])}</div>
                        ))
                        }
                      </div>))) :
                      (this.state.regexMatches.map((match, idxMatch) => (
                        <div key={idxMatch} className="resultItem">{match}</div>
                      )))}
                  </div>
                )
            }
          </div>
        </Paper>
      </div>
    )
  }
}

export default LiteViewer;