# Disjoint Set
we introduce you with a useful data structure called the disjoint set that can be implemented with
a forest of trees, and guide you to think about extending \disjoint-set forest" with binary search trees to
provide even more sophisticated functionality. The disjoint sets is also called partition, and is introduced
in Section 11.4.3 of the textbook. Let's first start with a story.

Suppose that you have n friends, and each friend initially owns a computer game. To make it simple,
the friends are numbered from 1 to n, and the game initially-owned by the i-th friend is numbered i.
In other words, the set of all games f1; 2; : : : ; ng is initially partitioned to n disjoint subsets (owned-byfriend)
f1g; f2g; : : : ; fng.

There are two kinds of incidents in our story. In the rst incident, as time goes by, some friends
find the computer games on hand tedious, and want to play other games. If the current owner u of the
i-th computer game finds it tedious, and gets a message on Facebook that the j-th computer game is
interesting, two possible results will take place:

- If u also owns the j-th computer game, u will simply switch to play her/his j-th game. No other
actions are needed.
- If u doesn't own the j-th computer game, u will visit the person who owns the j-th game, say
v, and borrow all v's computer games. Note that after this incident, v will no longer own any
computer game. That is, v will go study hard for the DSA homeworks (and will not be eligible
for borrowing games from other friends).

Another incident arises when you visit your friend who owns the i-th game one day. During the visit,
you find that your friend owns many games that are of interest to you. You check your pocket and find s
dollars. You then ask your friend about the price of each game she/he owns, with the hope of calculating
the maximum number of games you can buy (from the store nearby, not from your friend). To simplify
this problem, you will not actually go buy those from the store nearby nor your friend.

In this very last problem of the semester, you are asked to simulate the two scenarios with eficient
data structures and algorithms. Before you switch to the next page, we encourage everyone to stop and
think about how to solve the problem. We have sub-problems on the next page to help you conquer
the problem.
