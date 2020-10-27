import React from 'react';

import Container from '@material-ui/core/Container';
import Typography from '@material-ui/core/Typography';
import Grid from '@material-ui/core/Grid';

import LiteViewerREmatch from './LiteViewerREmatch';
import LiteViewerVs from './LiteViewerVs';

import english from '../text/english';
import { Divider } from '@material-ui/core';

const WORKPATH = `${process.env.PUBLIC_URL}/liteWork.js`;
let worker = new Worker(WORKPATH);

const AboutInterface = () => {
  return (
    <Container maxWidth="sm" className="mainContainer">
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
        <Typography variant="body2" align="center">
          <p>John Cook: +1983847673, john@cook.org</p>
          <p>Mark Twain: +56987346712, twai@hotmail.com</p>
          <p>Eduardo Hem: +56933671832, hem@rumbar.com</p>
        </Typography>
      </div>
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
          {english.section2.example1}
        </Typography>
        <LiteViewerVs
          idx="example1"
          worker={worker}
          text={english.section2.text1}
          rematch={english.section2.rematch1}
          regex={english.section2.regex1}
        />
      </div>
      <div className="sectionContainer">
        <Typography variant="subtitle2" color="primary">
          Example 2.
       </Typography>
        <Typography variant="body2" align="justify">
          {english.section2.example2}
        </Typography>
        <LiteViewerVs
          idx="example2"
          worker={worker}
          text={english.section2.text2}
          rematch={english.section2.rematch2}
        />
      </div>
    </Container>
  )
}

export default AboutInterface;