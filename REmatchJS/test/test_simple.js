const REmatch = require('../lib')
 try {
 // Ejemplo search
    console.time('Tiempo search');
    const text = 'Lorem ipsum dolor sit amet consectetur adipiscing elit euismod condimentum, conubia a mollis pulvinar nascetur taciti elementum praesent'
    let rgx1 = REmatch.compile('.*!word{dolor}.*');
    const result = rgx1.search(text).span('word');// error nros
    console.log(result);
    console.timeEnd('Tiempo search');

    // // Ejemplo find
    console.time('Tiempo find');
    const textt = 'Lorem ipsum dolor sit amet consectetur adipiscing elit euismod condimentum, conubia a mollis pulvinar nascetur taciti elementum praesent'
    let rgx11 = REmatch.compile('.*!word{dolor}.*');
    const result1 = rgx11.find(textt).span('word');
    console.log(result1);
    console.timeEnd('Tiempo find');

    // Ejemplo findIter
    console.time('Tiempo finditer')
    let rgx2 = REmatch.compile('.*!x{ly}.*');
    const text1 = "He was carefully disguised but captured quickly by police.";
    for (let r of rgx2.findIter(text1)) {
        console.log(r.span('x'))
    }
    console.timeEnd('Tiempo finditer')

    // Ejemplo findall
    console.time('Tiempo findall')
    const text2 = "He was carefully disguised but captured quickly by police.";
    let rgx3 = REmatch.compile('.*!adverb{ [a-zA-Z]+ly}.*');
    let list = rgx3.findall(text2);
    for (let index = 0; index < list.length; index++) {
      const element = list[index].group('adverb');
      console.log(element)
    }
    console.timeEnd('Tiempo findall')

    // Error nros
    const text3 = "sempiternal"
    let rgx8 = REmatch.compile('.*!word{[a-z]+}.*');
    let match5 = rgx8.find(text3);
    console.log(match5.group('word'));
    


 } catch(error) {
     console.log(error)
 }