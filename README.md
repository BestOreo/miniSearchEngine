# miniSearchEngine
Using C with pagerank algorithm

body {
font-size: 11pt;
font-family: arial, sans-serif;
margin: 10px 20px;
}
p {
margin-left:40px;
}
a {
color: blue;
text-decoration: none;
}

a.active {
color:blue;
text-decoration: none;
}

a.inactive {
color: #BBBBDD;
text-decoration: none;
}

a[href]:hover {
color: #CC0000;
background: #FFFFCC;
}

small {
font-size: 75%
}

pre {
background: #fcfcff;
border: thin dotted #e4e4f5;
margin: 5px 20px 5px 20px;
padding: 4px 8px;
border-radius: 10px;
}

tt {
font-size: 1.0em;
color: #107F80
}

span.toggle {
font-size: 67%;
}

span.notice {
font-size: 110%;
}

span.tiny {
font-size: 75%;
font-weight: normal;
}

span.heading {
font-size: 18pt;
color: #4444CC;
}

span.subheading {
font-size: 16pt;
color: #000000;
font-weight: normal;
}

span.marks {
font-weight: normal;
font-size: 75%;
}

span.identifier {
color: #993300;
font-size: 110%;
font-weight: bold;
font-family: courier;
}

span.contentLink {
font-weight: bold;
font-size: 110%
}

span.contentNote {
font-weight: normal;
font-size: 85%;
}

tr.heading {
font-size: large;
font-weight: bold;
background-color: #DDAA77;
}

table.note {
border: thin solid black;
padding: 2pt;
width: 75%
}

div.note {
border: thin solid black;
font-size: 90%;
margin: 5px 60px 5px 60px;
padding: 4px 8px;
}

dt {
margin-top: 10px;
}

dt.item {
font-weight: bold;
}

h2 {
font-size: 16pt;
font-weight: 300;
color: green;
background-color: aliceblue;
padding: 10px 20px;
border-radius: 8px;
border-bottom: 1px solid lightblue;

}

h3 {
font-size: 14pt;
font-weight: 300;
color: green;
}

.h2tt {
font-size: 17pt;
font-weight: 300;
color: #4444CC;
font-family: courier;
}

.h3tt {
font-size: 15pt;
font-weight: 300;
color: #4444CC;
font-family: courier;
}

.red {
color: #CC0000;
}

.green {
color: #006600;
}

.brown {
color: #993300;
}

.grey {
color: #AAAAAA;
}

.comment {
font-size: 90%;
color: #666666
}

.important {
font-weight: bold;
color: #CC0000;
}

.bigQ {
font-size: 13pt;
font-style: italic;
}

dd {
color: rgb(86, 86, 86);;
}

ul {
margin-left:40px;
}

li {
margin-top: 6px;
}

td{
border: 1px solid lightgrey;
}


## COMP9024: Assignment 2 Simple Graph structure-based Search Engine

[The specification may change.
A notice on the class web page will be posted after each revision,
so please check class notice board frequently.]

Change log:

*   Please read my answer to the following question:    [Input/output formats for Part-B and C](https://webcms3.cse.unsw.edu.au/COMP9024/18x1/forums/2689989).
*   Deadline extended to 11pm 02/02/2018, and submission instructions included
*   In Part-B example, "url101" should appear at the start, incorreclty it was displayed at the end! I have now changed it (and struck out the incorrect entry).

mars  url101 url25 url31 url101

## Objectives

*   to implement a simple search engine based on the well known PageRank algorithm (simplified).
*   to give you further practice with C and advanced data structures (Graph and BST ADTs)

## Admin

**Marks**15 marks towards total course marks
**Due**11pm Friday 02/02/2018 11.55pm Monday 29 January 2018. **Late
Penalty**2 marks per day off the ceiling.

Last day to submit this assignment is 5pm Tuesday 06
Friday 02 Feb 2018, of course with late penalty.
**Submit**
Read instructions in the ["Submission"](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/index.html#Submission) section below.


## Aim

In this assignment, your task is to implement a simple search engine using the well known algorithm PageRank, simplified for this assignment, of course!. You should start by reading the
wikipedia entries on the topic. Later I will also discuss these topics in the lecture.

*   [PageRank (read up to the section "Damping factor")](https://en.wikipedia.org/wiki/PageRank)

The main focus of this assignment is to build a graph structure, calculate  PageRanks and rank pages
based one these values. You don't need to spend time crawling, collecting and parsing weblinks for this assignment.
You will be provided with a collection of "web pages" with the required information for this assignment in a easy to
use format. For example, each page has two sections,

*   Section-1 contains urls representing outgoing links.
Urls are separated by one or more blanks, across multiple lines.
*   Section-2 contains selected words extracted from the url. Words are
separated by one or more spaces, spread across multiple lines.

_Hint:_ If you use fscanf to read the body of a section above, you do not need to impose any restriction on line length.  I suggest you should try to use this approach - use fscanf! However, if you want to read line by line using say fgets, you can assume that maximum length of a line would be 1000 characters.

_Hint:_ You need to use a dynamic data structure(s) to handle words in a file and across files, no need to know max words beforehand.

Example file url31.txt
#start Section-1

url2  url34  url1 url26
url52 url21
url74  url6 url82

#end Section-1

#start Section-2

Mars has long been the subject of human interest. Early telescopic observations
revealed color changes on the surface that were attributed to seasonal vegetation
and apparent linear features were ascribed to intelligent design.

#end Section-2


Your tasks in summary:

*   _Calculate PageRanks_: You need to create a graph structure that represents
a hyperlink structure of given collection of "web pages" and for each page (node in your graph) calculate  PageRank value
and other graph properties.
*   _Inverted Index_: You need to create "inverted index" that provides a list of pages for every word in a given collection of pages.
*   _Search Engine_: Your search engine will use the given inverted index to find pages where query
term(s) appear and rank these pages using their PageRank values (see below for  more details)

###  Sample files and Hints

*   [Sample1.zip](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/samples/Sample1.zip)
*   Hints on ["How to Implement Ass2"](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/HowToImplement-Ass2-PartA.pdf) will be discussed in the lecture.

### Additional files

You can submit additional supporting files, *.c and
*.h, for this
assignment. For example, you may implement your graph adt in files graph.c and graph.h and
submit these two files along with other required
files as mentioned below.

* * *

## Part-A: Calculate  PageRanks

You need to write a program in the file pagerank.c that reads data from a given collection of pages
in the file collection.txt
and builds a graph structure using Adjacency Matrix or List Representation.
Using the algorithm described below, calculate  PageRank  for every url in the file collection.txt. In
this file, urls are separated by one or more spaces or/and new line character.
Add suffix .txt to a url to obtain file name of the corresponding "web page". For example, file url24.txt
contains the required
information for url24.

Example file collection.txt
url25   url31 url2
url102   url78
url32  url98 url33


Simplified PageRank Algorithm (for this assignment)

**PageRank(d, diffPR, maxIterations)**

Read "web pages" from the collection in file "collection.txt"
and build a graph structure using Adjacency List Representation

N = number of urls in the collection
For each url _pi_ in the collection
![](./COMP9024 18x1 - Assignment 2_files/fig_pr_0.png)
End For

iteration = 0;
diff = diffPR;   // to enter the following loop

While (iteration < maxIteration AND diff >= diffPR)
iteration++;

![](./COMP9024 18x1 - Assignment 2_files/fig_pr.png)
where,
- ![](./COMP9024 18x1 - Assignment 2_files/fig_M_P_i.png) is a set containing links(urls) pointing to pi
(ignore self-loops and parallel edges)
- ![](./COMP9024 18x1 - Assignment 2_files/fig_L.png) is out degree of ![](./COMP9024 18x1 - Assignment 2_files/fig_p_j.png)
- ![](./COMP9024 18x1 - Assignment 2_files/fig_t_1.png) corresponds to value of "iteration"

![](./COMP9024 18x1 - Assignment 2_files/fig_diff.png)

End While


Your program in pagerank.c will take three arguments
(**d** - damping factor, **diffPR** - difference in PageRank sum, **maxIterations** - maximum iterations)
and using the algorithm described in this section, calculate  PageRank for every url.

For example,


% pagerank 0.85  0.00001  1000


Your program should output a list of urls in descending order of  PageRank values
(use format string "%.7f") to a file
named pagerankList.txt.
The list should also include out degrees (number of out going links) for each url, along with its  PageRank value.
The values in the list should be comma separated. For example, pagerankList.txt may contain the following:

Example file pagerankList.txt
url31, 3, 0.2623546
url21, 1, 0.1843112
url34, 6, 0.1576851
url22, 4, 0.1520093
url32, 6, 0.0925755
url23, 4, 0.0776758
url11, 3, 0.0733884


#### Sample Files for Part-A

You can download the following three sample files with expected pagerankList.txt files.

Use format string "%.7f" to output pagerank values.
Please note that your pagerank values might be slightly different
to that provided in these samples. This might be due to the way you carry out calculations.
However, make sure that your pagerank values match to say first 6 decimal points to the expected values.
For example, say an expected value is  0.1843112, your value could be 0.184311x where x could be any digit.

All the sample files were generated using the following command:

% pagerank  0.85  0.00001  1000


*   [aEx1](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/samples/aEx1.zip)
*   [aEx2](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/samples/aEx2.zip)
*   [aEx3](http://www.cse.unsw.edu.au/~cs9024/18x1/assn/assn2/samples/aEx3.zip)

## Part-B: Inverted Index

You need to write a program in the file named inverted.c that reads data from a given collection of pages in
collection.txt and generates an "inverted index" that provides a sorted list (set) of urls for every word in a
given collection of pages. Before inserting words in your index, you need to "normalise" words by,

*   removing leading and trailing spaces,
*   converting all characters to lowercase,
*   remove the following punctuation marks, if they appear at the end of a word:

'.' (dot), ',' (comma), ';' (semicolon), ? (question mark)

In each sorted list (set), duplicate urls are not allowed.
Your program should output this "inverted index" to a file named invertedIndex.txt.
One line per word, words should be alphabetically ordered, using ascending order.
Each list of urls (for a single word) should be alphabetically ordered, using ascending order.

Example file invertedIndex.txt
design  url2 url25 url31 url61
mars  url101 url25 url31 url101
vegetation  url31 url61


## Part-C: Search Engine

Write a simple search engine in file searchPagerank.c that given search terms (words) as commandline
arguments, finds pages with one or more search terms and
outputs (to stdout) top 30 pages  in descending order of number of search terms found and then within each group, descending order of  PageRank.
If number of matches are less than 30, output all of them.

Your program must use data available in two files invertedIndex.txt and pagerankList.txt, and must
derive result
from them. We will test this program independently to your solutions for "A" and "B".

Example:


% searchPagerank  mars  design
url31
url25


* * *

## Submission

**Additional files:** You can submit additional supporting files, *.c and *.h,
for this assignment.

IMPORTANT: Make sure that your additional files (*.c) DO NOT have "main" function.

For example, you may implement your graph adt in files graph.c and graph.h and
submit these two files along with other required
files as mentioned below. However, make sure  that these files do not have "main" function.

I explain below how we will test your submission, hopefully this will answer all of your questions.

You need to submit the following files, along with your supporting files (*.c and *.h):

*   pagerank.c
*   inverted.c
*   searchPagerank.c

Now say we want to mark your pagerank.c program. The auto marking program will take all your supporting files
(other *.h and *.c) files, along with pagerank.c and execute the following command to generate executable
file say called pagerank. Note that the other two files from the above list
(inverted.c and searchPagerank.c) will be removed from the dir:

% gcc -Wall -lm -Werror *.c  -o pagerank

So we will **not use your Makefile** (if any). The above command will generate object files from your supporting
files and the file to be tested (say pagerank.c), links these object files and generates executable file,
say pagerank in the above example. Again, please make sure that you **DO NOT have main function in your supporting files** (other *.c files you submit).

We will use similar approach to generate other two executables
(for inverted.c and  searchPagerank.c).

### How to Submit

Go to the following submission page, select the tab named "Make Submission", and follow the instructions.

*   [Assignment 2 Submission Page](https://webcms3.cse.unsw.edu.au/COMP9024/18x1/resources/13898)

* * *

## Plagiarism

You are allowed to use code from the course material (for example, available as part of the labs, lectures and tutorials). If you use code from the course material, please **clearly acknowledge** it by including a comment(s) in your file. If you have questions about the assignment, ask your tutor.

Your program must be entirely your own work. Plagiarism detection software compares all submissions pairwise (including submissions for similar projects in previous years, if applicable) and serious penalties will be applied, particularly in the case of repeat offences.

**_Do not copy from others; do not allow anyone to see your code, not even after the deadline_**

Please refer to the on-line sources to help you understand what plagiarism is and how it is dealt with at UNSW:

*   [Plagiarism and Academic Integrity](https://student.unsw.edu.au/plagiarism)
*   [UNSW Plagiarism Procedure](https://www.gs.unsw.edu.au/policy/documents/plagiarismprocedure.pdf)

Before submitting any work you should read and understand the sub section named _**Plagiarism**_ in the course outline.
We regard unacknowledged copying of material, in whole or part, as an extremely serious offence.
For further information, see [the course outline](https://webcms3.cse.unsw.edu.au/COMP9024/18x1/outline).

* * *

-- end --
