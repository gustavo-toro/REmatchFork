const english = {
  section1: {
    title: '5 minutes introduction to RegEx',

    subtitle1: 'What the whole is this RegEx thing?',
    body1: 'When processing data sometimes you might be interested in finding certain patterns in that data. For example, imagine you have a document where you note information about all of your friends, such as their name, their phone number, and their email. An instance of such an information sheet might be the following:',
    body2: 'Imagine now that you need all the emails on this list (also imagine that the list has many more lines). How do you obtain those? Quite simple: using regular expressions. Regular expressions (regex) are commands that allow you to find certain patterns in the text you are processing. A regular expression that would allow us to highlight all of the emails in the text such as the one above is: “, ([a-zA-Z])*@([a-zA-Z])*.([a-zA-Z])*\n”. Intuitively, this expression searches the text until encountering a comma “,”. It then reads any sequence of the letters of the english alphabet. This is denoted as ([a-zA-Z])*, where [a-zA-Z] denotes all the lower case and uppercase letters, while the star symbol * signals that any sequence of such letters is allowed. The next symbol, “@” forces us to encounter the at part of an email address, again followed by any sequence of letters, followed by a dot “.”, and then followed by another sequence of letters, before reaching the end of the line, denoted “\n”. (For more complex domains, such as “ing.puc.cl”, a similar expression can be constructed).',
  },
  section2: {
    title: 'What is REmatch?',

    subtitle1: 'Another library for running regular expressions?',
    body1: 'No. REmatch is different from other regex libraries. Regarding evaluating simple regular expressions (without grouping), REmatch has no differences, and it runs as fast as other libraries.  However, suppose you want to extract info rmation. In that case, REmatch is different: REmatch looks for ALL POSSIBLE matches of your regular expression with the document. For example, take a look at this regular expression with variable and the analog version evaluated in PCRE (javascript).',

    example1: 'Intuitively, here we are skipping to some dot symbol \. (or the beginning of the document ^ to capture the very first sentence) in the text, and then storing the text until the next dot symbol in the variable !x. This corresponds to extracting the sentence into !x, and then traversing until the end of the text using the .* operation. In this example, we assume that text has no new line symbols. Should these be present, we might need to replace each occurence of \. with [\.\n]. Similarly, if we want to consider questions and exclamations, the ? and ! symbols should be included in this list.',
    text1: 'You don’t know about me without you have read a book by the name of The Adventures of Tom Sawyer; but that ain’t no matter.  That book was made by Mr. Mark Twain, and he told the truth, mainly.  There was things which he stretched, but mainly he told the truth.  That is nothing.  I never seen anybody but lied one time or another, without it was Aunt Polly, or the widow, or maybe Mary.  Aunt Polly—Tom’s Aunt Polly, she is—and Mary, and the Widow Douglas is all told about in that book, which is mostly a true book, with some stretchers, as I said before.',
    rematch1: '!x{You}',
    regex1: '(You)',

    example2: 'TODO',
    text2: 'Texto de ejemplo',
    rematch2: '!a{.*}',
  }

}

export default english;