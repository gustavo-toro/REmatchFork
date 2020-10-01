// eslint-disable-next-line no-undef
importScripts('./rematch_wasm.js');

// eslint-disable-next-line no-undef
const { RegEx, RegExOptions } = Module;
const CHUNK_SIZE = 10000;
const MESSAGE_SIZE = 20000;

this.onmessage = (m) => {
    try {
        let i = 0;
        let count = 0;
        let currMatch = [];
        let matches = [];

        let rgxOptions = new RegExOptions();
        rgxOptions.early_output = true;
        let rgx = new RegEx(`.*${m.data.query}.*`, rgxOptions);

        /* THIS SHOULD BE IN RegEx OBJECT */
        let schema = [...m.data.query.matchAll(/!([A-Za-z0-9]+)/g)].map((m) => (m[1]));
        this.postMessage({
            type: 'SCHEMA',
            payload: schema,
        })
        /* THIS SHOULD BE IN RegEx OBJECT */

        let s = 0;
        let e = CHUNK_SIZE;
        let match;
        console.log('MESSAGE RECEIVED');
        while (s < m.data.text.length) {
            rgx.feed(m.data.text.slice(s, e));
            while ((match = rgx.internalFindIter())) {
                schema.forEach((variable) => {
                    console.log(variable, ':', match.span(variable));
                });
            }
            s = e;
            e += CHUNK_SIZE;
        }
/*
        while ((match = rgx.findIter(m.data.text))) {

            schema.forEach((variable) => {
                currMatch.push(match.span(variable));
            });
            
            matches.push(currMatch);
            currMatch = [];
            count++;

            if (matches.length === MESSAGE_SIZE) {
                console.log('SEND CHUNK');
                this.postMessage({
                    type: 'MATCHES',
                    payload: matches,
                })
                matches = [];
                count = 0;
            }
            
        }*/
/*
        if (matches.length > 0) {
            console.log('SEND LAST CHUNK');
            this.postMessage({
                type: 'MATCHES',
                payload: matches,
            });
        }
*/
        rgxOptions.delete();
        rgx.delete();

    } catch (err) {
        this.postMessage({
            type: 'ERROR',
            payload: err,
        });
    }
}