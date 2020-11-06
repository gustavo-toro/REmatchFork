import React from 'react';

import Container from '@material-ui/core/Container';
import Typography from '@material-ui/core/Typography';
import Paper from '@material-ui/core/Paper';

import LiteViewer from './LiteViewer';
import Viewer from './Viewer';

import english from '../text/english';

const WORKPATH = `${process.env.PUBLIC_URL}/liteWork.js`;
let worker = new Worker(WORKPATH);

const About = () => {
  return (
    <Container maxWidth="sm" className="mainContainer">
      <h1>Under construction...</h1>
      <div className="sectionContainer">
        <Viewer
          idx="rematch"
          worker={worker}
          text={english.section2.text1}

          rematch={'!x{.+}!y{.+}before..*'}
        />
        <Viewer
          idx="regex"
          worker={worker}
          text={english.section2.text1}

          regex={'You'}
        />
        <Viewer
          idx="both"
          worker={worker}
          text={english.section2.text1}

          rematch={'!x{You}.*!y{.}.*'}
          regex={'You'}
        />
      </div>
      {/* 5 MIN REGEX */}
      <Typography variant="h5" color="primary" align="center">
        {english.section1.title}
      </Typography>
      <div className="sectionContainer">
        <Typography variant="subtitle1" color="primary">
          {english.section1.subtitle1}
        </Typography>
        <Typography variant="body2" align="justify">
          {english.section1.body1}
        </Typography>
      </div>
      <Paper className="codeBlock" elevation={3}>
        <p>John Cook: +1983847673, john@cook.org</p>
        <p>Mark Twain: +56987346712, twai@hotmail.com</p>
        <p>Eduardo Hem: +56933671832, hem@rumbar.com</p>
      </Paper>
      <div className="sectionContainer">
        <Typography variant="body2" align="justify">
          {english.section1.body2}
        </Typography>
      </div>
      <br />
      {/* WHAT IS REMATCH? */}
      <Typography variant="h5" color="primary" align="center">
        {english.section2.title}
      </Typography>
      <div className="sectionContainer">
        <Typography variant="subtitle1" color="primary">
          {english.section2.subtitle1}
        </Typography>
        <Typography variant="body2" align="justify">
          {english.section2.body1}
        </Typography>
      </div>
      <div className="sectionContainer">
        <Typography variant="subtitle2" color="primary">
          Example 1.
       </Typography>
        <Typography variant="body2" align="justify">
          {english.section2.body1}
        </Typography>
        <LiteViewer
          idx="example1"
          worker={worker}
          text={english.section2.text1}
          rematch={english.section2.rematch1}
          regex={english.section2.regex1}
        />
      </div>
    </Container>
  )
}

export default About;