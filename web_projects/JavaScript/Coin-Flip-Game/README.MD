# Coin Flip Guess Game

A simple web game where you guess **Heads** or **Tails** and see if you win.

## How to Play
1. Click **Heads** or **Tails**.
2. The computer flips a coin.
3. If your guess matches → You win.
4. If not → You lose.
5. Click **Reset Score** to clear results.

## Features
- Random coin flip
- Tracks wins and losses
- Saves score using localStorage
- Reset score button

## How to Run
1. Save the file as `index.html`.
2. Open it in any web browser.

## Note
If results don’t display correctly, use template strings:

```js
document.querySelector('.js-coin').innerHTML = `The coin is ${compGuess}`;
document.querySelector('.js-result').innerHTML = `You guessed ${playerGuess}. ${result}`;
document.querySelector('.js-score').innerHTML = `Wins: ${score.wins}, Losses: ${score.loses}`;