## Introduction

The goal of my final project is to apply algorithms on various language data sets and create a visualization to showcase my findings. By languages, I specifically mean the frequency data sets for languages, as in how frequently a word is used in one language relative to another. I would like to apply several algorithms on these data sets and potentially discover something new.

## Organizing The Datasets

Most of the data sets are from various frequency dictionaries. They usually included the frequency of the given word, the translation, and the precise number that the word was used given the sample size. Frequency dictionaries can compile up to 5000 words, yet I was only interested in the first 900.

Putting the data into understandable and coherent .txt files was a challenge. For most of the languages, I had a .txt file made but the data included other unnecessary information such as the exact number a word was used, yet I was only interested in the raw listing of the most frequent words.

To fix this, I had the Data class, which loaded in the .txt file and performed several cleaning operations such as removing white space, unnecessary or invalid characters, and duplicate words. I was only interested in the first 900 non-duplicate and most frequent words.

Another challenge was translating the non-english data sets to english, and the same process described above took place. The reason I was interested in this is because I wanted to perform some analysis on the similarities between these languages and english was the common ground. Several cleaning operations took place in the Analysis class as well.

## Tests

The only class that required significant testing was the Grid class. The reason this is the case is because the Data class was mostly used to perform basic file-reading and cleaning operations while the Analysis class performed mathematical computations. Therefore more tests were added for the Grid class, since it was templated and its functionality expanded.

## The Analysis

### Storing the data 

The data was stored in two ways: through a vector of Grid-class matrices, where each language and its translated counterpart is stored as a 900-length matrix, and as a LanguageData object, in the case where having a 900-length vector might be more beneficial. One particular challenge was loading the data in efficiently without hard-coding 10> different files. 

The solution was a const vector which stored the names of the .txt files. The vector was traversed and the files were loaded and stored in the method described above. Another const vector was used to store the particular indices in the first const vector where english-translated languages were stored. I needed the english version of the languages because these were needed to perform many of the calculations.

### The most frequent lengths, the most common color

The following computation was performed in two ways: first on the top 10% of the most frequent words (or the top 90 of 900) and second, on the entire 900-length data sets. The results were surprsing and are found in the visualization. Overall, this was a fairly straightforward calculation.

The most common color computation was performed by using the translated-language data sets. I used another const vector that stores the most common colors. A traversal of the data sets was performed, the most common colors were identified, and then the indices where the most common colors showed up (e.g. "red" appears 98th among the most common words in enlgish) were stored.

The results are available on the visualization.

### A language distribution

One thing I was interested in is given the raw frequency numbers and the sample size, what does the distribution of the most frequent words look like? The main computation here is organizing the data such that the words were removed and the numbers were emphasized. This was a relatively easy computation, yet I solely did it for english.

## Libraries

Three main libraries were used, all of them in the visualization and all of them are in javascript. They are: D3.js, Canvas.js, and Sigma.js. The first two were used in the creation of all the bar/column visualizations while the Sigma.js was used to create the graph visualization and populate the nodes and edges.

## The Visualization

Canvas.js and D3.js were very helpful in creating the bar/column charts for the first three visualizations. I first needed to create an HTML/CSS website however, and to provide details about my project. This was done easily after time spent googling around. It was a little time consuming however.

The graph visualization was probably the hardest part of this process, because I had little experience with Sigma.js and I had trouble defining how to use the graph. I ended up using it for the most common color visualization and, after creating several sample graphs and messing around, I was able to do it.
