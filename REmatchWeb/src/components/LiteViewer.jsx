import React, { Component } from 'react';

import Paper from '@material-ui/core/Paper';
import Divider from '@material-ui/core/Divider';
import Pagination from '@material-ui/lab/Pagination';

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

class LiteViewer extends Component {
  constructor(props) {
    super(props);
    this.state = {
      query: props.query,
      text: props.text,
      idx: props.idx,
    };
  }

  componentDidMount() {
    let queryEditor = CodeMirror(document.getElementById(`queryEditor-${this.props.idx}`), {
      value: this.props.query,
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
      lineNumbers: true,
      scrollbarStyle: 'native',
      smartIndent: false,
      indentWithTabs: true,
      undoDepth: 100,
      viewportMargin: 15,
      readOnly: 'nocursor',
    });
  }
  render() {
    return (
      <Paper className="paperLite">
        <div className="queryEditor" id={`queryEditor-${this.props.idx}`}></div>
        <Divider variant="middle"/>
        <div className="textEditor" id={`textEditor-${this.props.idx}`}></div>
        <Divider variant="middle"/>
        <div className="results">
          Result blabla
        </div>
        <Divider variant="middle"/>
        <div className="pagination" >
          <Pagination count={10} size="small" />
        </div>
      </Paper>
    )
  }
}

export default LiteViewer;