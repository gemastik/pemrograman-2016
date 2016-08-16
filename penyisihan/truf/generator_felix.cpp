#include <string>
#include <map>
#include <random>

#include <cassert>
#include <cstdio>
#include <cmath>

using namespace std;

/*

Truf is a popular Indonesian trick-taking card game with bidding.
In this problem, we are examining a very special case of the simplified version
of the game. You do not need to understand Truf game to solve this problem.

In this game, we only consider 4 players where each player initially has 13 cards, and about to
start the first round. You are the first player and start first.
You deal one card from the 13 cards in your hand.
Then the rest of the three players each deals one of their cards following these rules:
- The card must have the same suit that were dealt by the first player.
- If the player doesn't have a card with the same suit, any card can be played.
The winner of the first round is the player who dealt the highest card of
the same suit with the first player.

As the first player, you have 13 choices to deal a card in the first round,
and you want to know what is the probability of winning the first round
for each of the 13 choices.
The rest of the players will pick the best move to help the first player win
the first round.

Notes:
- The cards consist of 4 suits: D (diamond), C (club), H (heart), S (spade).
- Each suit has 13 values ranked from the lowest to the highest: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A.
- The 52 cards are dealt with uniform probability to the 4 players.

Input
The first line contains an integer N denoting the number of test cases.
The next N lines each describes a game where you are given the 13 cards that are in your hand.

Output
For each game, output 13 lines (in the order of the input) each containing a
card and the probability of winning the first round if you were to dealt
that card, followed by a blank line.
Print the probability in percentage up to to 3 decimal places.
See the sample output for the format.


Sample Input
2
6D 8C 9C TC 9H JH KH AH 3S 4S 7S 9S JS
6D JD QD 6C 7C JC 3H KH 2S 8S TS JS AS

Sample Output
6D: 48.750%
8C: 81.457%
9C: 81.457%
TC: 81.457%
9H: 91.605%
JH: 96.805%
KH: 100.000%
AH: 100.000%
3S: 0.006%
4S: 0.006%
7S: 29.988%
9S: 54.975%
JS: 73.722%

6D: 50.347%
JD: 94.891%
QD: 94.891%
6C: 50.347%
7C: 50.347%
JC: 89.697%
3H: 0.000%
KH: 98.876%
2S: 0.000%
8S: 73.722%
TS: 86.499%
JS: 86.499%
AS: 100.000%



Side Story (not related to this problem):
Sonny is often bidding zero and failed miserably on the first round,
wouldn't it be great to have a program that tells whether it's good to bid zero
for the cards at hand? (assuming no Truf or Truf is very unlikely to appear in the first round).

*/

static int random_range(int n) {
  static mt19937 gen(14);
  static uniform_int_distribution<int> dis[52];
  static bool inited = false;
  if (!inited) {
    for (int i = 0; i < 52; i++) {
      dis[i] = uniform_int_distribution<int>(0, i);
    }
    inited = true;
  }
  return dis[n - 1](gen);
}

const char *rank_str = "23456789TJQKA";
const char *suit_str = "DCHS";

long long random_hand(long long &used) {
  long long hand = 0;
  int n = 52 - __builtin_popcountll(used);
  int need = 13;
  for (int i = 0; i < 52; i++) {
    long long c = 1LL << i;
    if (!(used & c) && random_range(n--) < need) {
      hand |= c;
      if (--need == 0) {
        break;
      }
    }
  }
  used |= hand;
  return hand;
}

void check_random_hands() {
  int cnt[52][4] = { 0 };
  int n = 20000000;

  for (int i = 0; i < n; i++) {
    long long used = 0;
    for (int k = 0; k < 4; k++) {
      long long hand = random_hand(used);
      for (int j = 0; j < 52; j++) {
        if (hand & (1LL << j)) {
          cnt[j][k]++;
        }
      }
    }
    assert(used == (1LL << 52) - 1);
  }

  for (int i = 0; i < 52; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%10d", cnt[i][j]);
    }
    puts("");
  }
}

void print_bits(long long b, int nth) {
  for (int i = 0; i < 52; i++) {
    if (nth == i) printf("[");
    if (b & (1LL << i)) {
      printf("%d", 1);
    } else {
      printf("%d", 0);
    }
    if (nth == i) printf("]");
  }
  puts("");
}

int lowest_rank(long long c, int suit) {
  for (int i = 0; i < 13; i++) {
    int j = suit * 13 + i;
    if (c & (1LL << j)) return i;
  }
  return -1;
}

// Is there someone (b, c, or d) has higher card?
bool is_winning(int card, long long b, long long c, long long d) {
  int suit = card / 13;
  int rank = card % 13;
  return (lowest_rank(b, suit) < rank)
      && (lowest_rank(c, suit) < rank)
      && (lowest_rank(d, suit) < rank);
}

string to_str(int card) {
  int r = card % 13, s = card / 13;
  char str[10];
  sprintf(str, "%c%c", rank_str[r], suit_str[s]);
  return str;
}

vector<int> winCount(long long felix_hand, int n) {
  vector<int> win_count(52);

  long long used = felix_hand;
  for (int i = 0; i < n; i++) {
    long long used2 = used;
    long long risan_hand = random_hand(used2);
    long long sonny_hand = random_hand(used2);
    long long danil_hand = random_hand(used2);
    assert(used2 == (1LL << 52) - 1);

    for (int j = 0; j < 52; j++) {
      if (felix_hand & (1LL << j)) {
        if (is_winning(j, risan_hand, sonny_hand, danil_hand)) {
          win_count[j]++; // is winning for first player.
        }
      }
    }
  }

  return win_count;
}

void generate(long long felix_hand) {
  int n = 100000;

  vector<int> win_count = winCount(felix_hand, n);

  vector<pair<string, int> > cards;
  for (int j = 0; j < 52; j++) {
    if (felix_hand & (1LL << j)) {
      string card = to_str(j);
      cards.push_back(make_pair(card, win_count[j]));
    }
  }
  random_shuffle(cards.begin(), cards.end());
  for (int i = 0; i < cards.size(); i++) {
    if (i) fprintf(stdout, " ");
    pair<string, int> card = cards[i];
    fprintf(stdout, "%s", card.first.c_str());
    fprintf(stderr, "%s: %.3lf%%\n", card.first.c_str(), 100.0 * card.second / n);
  }
  fprintf(stdout, "\n");
  fprintf(stderr, "\n");
}

void iogen() {
  freopen("kartu.in", "w", stdout);
  freopen("kartu.ans", "w", stderr);

  int T = 50;
  vector<long long> felix_hand;
  for (int i = 0; i < T; i++) {
    long long used = 0;
    felix_hand.push_back(random_hand(used));
  }

  fprintf(stdout, "%d\n", T);
  for (int i = 0; i < T; i++) {
    generate(felix_hand[i]);
  }
}

void normal() {
  int T;
  scanf("%d", &T);
  while (T--) {
    long long used = 0;
    vector<int> cards;
    for (int i = 0; i < 13; i++) {
      char s[10];
      scanf("%s", s);
      int r = strchr(rank_str, s[0]) - rank_str;
      int c = strchr(suit_str, s[1]) - suit_str;
      int j = c * 13 + r;
      cards.push_back(j);
      used |= 1LL << j;
    }
    assert(__builtin_popcountll(used) == 13);
    int n = 50000000;
    vector<int> win_count = winCount(used, n);
    for (int j : cards) {
      printf("%s: %.0lf%%\n", to_str(j).c_str(), 100.0 * win_count[j] / n);
    }
    puts("");
  }
}

int main() {
  // normal();

  // Note: this produces input and output. The output is not accurate.
  // Use kartu-risan.cc to get accurate output.
  iogen();
}
