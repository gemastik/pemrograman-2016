#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const char* nums = "0123456789TJQKA";

struct Card {
  int num;
  char suit;

  Card(const string& cardString) {
    num = getNum(cardString);
    suit = cardString[1];
  }

  bool operator<(const Card& c) const {
    return c.suit != suit || c.num < num;
  }

 private:
  int getNum(const string& cardString) {
    switch(cardString[0]) {
      case 'T': return 10;
      case 'J': return 11;
      case 'Q': return 12;
      case 'K': return 13;
      case 'A': return 14;
    }
    return (int)(cardString[0]) - 48;
  }
};

double C_[53][14];

double C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  if (k == 0 || k == n) {
    return 1;
  }
  double &ret = C_[n][k];
  if (ret == ret) {
    return ret;
  }
  return ret = C(n - 1, k) + C(n - 1, k - 1);
}

double dp[13][13][4];

double doDP(int smaller, int larger, int player) {
  if (player == 0) {
    return smaller == 0 && larger == 0;
  }
  double &ret = dp[smaller][larger][player];
  if (ret == ret) {
    return ret;
  }
  ret = 0;
  int numCards = player * 13;
  for (int i = 1; i <= min(smaller, 13); i++) {
    for (int j = 0; j <= larger && i + j <= 13; j++) {
      double p =
          C(smaller, i) * C(larger, j)
             * C(numCards - smaller - larger, 13 - i - j) / C(numCards, 13);
      ret += p * doDP(smaller - i, larger - j, player - 1);
    }
  }
  double p = C(numCards - smaller - larger, 13) / C(numCards, 13);
  ret += p * doDP(smaller, larger, player - 1);
  return ret;
}

double getWinningProb(const vector<Card> &cards, const Card& card) {
  int smaller = card.num - 2;
  int larger = 12 - smaller;
  for (Card c : cards) {
    if (c.suit != card.suit) {
      continue;
    }
    if (c.num < card.num) {
      smaller--;
    } else if (c.num > card.num) {
      larger--;
    }
  }
  return doDP(smaller, larger, 3);
}

int main() {
  memset(C_, -1, sizeof(C_));
  memset(dp, -1, sizeof(dp));
  int nTC;
  cin >> nTC;
  for (int tc = 0; tc < nTC; tc++) {
    vector<Card> cards;
    for (int i = 0; i < 13; i++) {
      string cardString;
      cin >> cardString;
      cards.emplace_back(cardString);
    }
    if (tc) printf("\n");
    for (Card c : cards) {
      printf("%c%c: %.5lf%%\n", nums[c.num], c.suit, getWinningProb(cards, c) * 100);
    }
  }

  return 0;
}
