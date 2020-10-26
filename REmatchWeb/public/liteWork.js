// eslint-disable-next-line no-undef
importScripts('./rematch_wasm.js');

const { RegEx, RegExOptions } = Module;

this.onmessage = (m) => {
  let matches = [];
  let currMatch = {};
  let match;
  let rgxOptions = new RegExOptions();
  rgxOptions.early_output = false;
  let rgx = new RegEx(`.*${m.data.query}.*`, rgxOptions);

  /* THIS SHOULD BE IN RegEx OBJECT */
  let schema = [...m.data.query.matchAll(/!([A-Za-z0-9]+)/g)].map((m) => (m[1]));
  this.postMessage({
    type: 'SCHEMA',
    payload: schema,
  });

  while ((match = rgx.findIter(m.data.text))) {
    schema.forEach(variable => {
      currMatch[variable] = match.span(variable);
    })
    matches.push(currMatch);
    currMatch = {};
  }

  this.postMessage({
    type: 'MATCHES',
    payload: matches,
  });
  rgxOptions.delete();
  rgx.delete();
}