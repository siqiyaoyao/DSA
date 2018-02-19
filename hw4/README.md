# Decision Tree
In this problem, we will explore an application of trees in the area of Artificial Intelligence and Machine
Learning. Decision Tree is one of the earliest tool for Machine Learning. The non-leaf nodes of a decision
tree represent choices (factors) considered, while the leaf nodes represent final decisions under the choices.
For simplicity, we will consider the trees with binary factors|i.e., binary decision trees. Such a tree is
shown in Example 7.8 of the textbook.

For instance, the following tree1 is a binary decision tree for deciding whether to play golf. If the sky
is cloudy, we decide to play golf; if not, we check if it is windy|if so, we play golf only if it is not humid
and the sky is clear. On the other hand, if it is not windy, we do not play golf only when the sky is not
rainy but it is humid.

In this problem, we ask you to implement such a program that can be taught with examples of
numerical variables and produces the binary decision tree. One interesting thing about binary decision
trees is that you can output the tree as some C code if(...)f...g elsef...g. That is, after you teach
your program, it can automatically produce another program that can make future decisions.
