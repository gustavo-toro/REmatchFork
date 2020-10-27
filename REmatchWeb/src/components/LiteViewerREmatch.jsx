import React, { Component } from 'react';

import Paper from '@material-ui/core/Paper';
import Divider from '@material-ui/core/Divider';
import Button from '@material-ui/core/Button';

import PlayArrow from '@material-ui/icons/PlayArrow';

/* CodeMirror */
import CodeMirror from 'codemirror';
import 'codemirror/theme/material-darker.css';
import 'codemirror/addon/mode/simple';

CodeMirror.defineSimpleMode('rematchQuery', {
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

class LiteViewerREmatch extends Component {
  constructor(props) {
    super(props);
    this.state = {
      rematch: props.rematch,
      text: props.text,
      idx: props.idx,
      idle: true,
      schema: [],
      matches: [],
      worker: props.worker,
    };
  }

  componentDidMount() {
    let queryEditor = CodeMirror(document.getElementById(`queryEditor-${this.props.idx}`), {
      value: this.props.rematch,
      mode: 'rematchQuery',
      theme: 'material-darker',
      lineNumbers: false,
      scrollbarStyle: null,
      smartIndent: false,
      indentWithTabs: true,
      undoDepth: 100,
      viewportMargin: 10,
      readOnly: 'nocursor',
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
    return this.state.textEditor.getRange(this.state.textEditor.posFromIndex(span[0]), this.state.textEditor.posFromIndex(span[1])).replace(' ', '␣');
  }

  handleRun() {
    this.setState({ idle: false });
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
          this.setState({ matches: m.data.payload});
          break;
        default:
          break;
      }
    }
  }

  render() {
    return (
      <div>
        <Paper className="paperLite">
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
                    {this.state.matches.map((match, idxMatch) => (
                      <div key={idxMatch} className="resultRow">
                        {Object.keys(match).map((variable, idxVariable) => (
                          <div key={idxVariable} className={`cm-m${idxVariable} resultItem`}>{variable}: {this.getText(match[variable])}</div>
                        ))
                        }
                      </div>
                    ))}
                  </div>
                )
            }
          </div>
        </Paper>
      </div>
    )
  }
}

export default LiteViewerREmatch;