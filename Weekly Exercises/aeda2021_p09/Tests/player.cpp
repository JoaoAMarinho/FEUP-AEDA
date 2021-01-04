#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    unsigned res=0;
    for (Bet bet:bets){
        if(bet.contains(num)) res++;
    }
	return res;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
    for (Bet bet:bets){
        if(bet.countRights(draw)>3) res.insert(bet);
    }
	return res;
}
