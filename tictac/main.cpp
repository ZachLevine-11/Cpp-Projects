#include <sstream>
#include <iostream>
#include <string>
#include <vector>

int printGameStatus(std::vector<std::vector<char> > gameBoard){
    //Print the top of the game board.
    //The game board should have walls too..
    std::cout << gameBoard[0][0] << "|" << gameBoard[0][1] << "|" << gameBoard[0][2] << "\n";
    std::cout << gameBoard[1][0] << "|" << gameBoard[1][1] << "|" << gameBoard[1][2] << "\n";
    std::cout << gameBoard[2][0] << "|" << gameBoard[2][1] << "|" << gameBoard[2][2] << "\n";
    //Print the bottom of the game board.
    return 0;
}

//Check if the game is a draw: true indicates draw, and false indicates that the game is not a draw.
bool isDraw(std::vector<std::vector<char> > gameBoard){
    for (int rowCounter = 0; rowCounter < 3; rowCounter++){
        for (int colCounter = 0; colCounter < 3; colCounter++){
            char square = gameBoard[rowCounter][colCounter];
            //If there is still an empty space in the game, then the game can be played and it is not a draw.
            if (square == ' '){
                bool status = false;
                return status;
            }
        }
    }
    //If we've reached this far, there are no empty spaces in the game, and the game is a draw.
    bool status = true;
    return status;
}


//Scoring function for terminal states of the game.
int minimax_score(std::vector<std::vector<char> > gameBoard, int depth, char playerSymbol){
    for (int i = 0; i<3; i++){
        if (gameBoard[i][0]==gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] != ' ') {
            if (gameBoard[i][0] == playerSymbol){
                return +10;
            }
            else{
                return -10;
            }
        }
    }
    for (int j = 0; j<3; j++){
        if (gameBoard[0][j]==gameBoard[1][j] && gameBoard[1][j]==gameBoard[2][j]  && gameBoard[0][j] != ' '){
            if (gameBoard[0][j] == playerSymbol){
                return +10;
            }
            else{
                return -10;
            }
        }
    }
        // Checking for Diagonals for X or O victory.
    if (gameBoard[0][0]==gameBoard[1][1] && gameBoard[1][1]==gameBoard[2][2] && gameBoard[0][0] != ' ') {
        if (gameBoard[0][0] == playerSymbol){
            return +10;
        }
        else{
            return -10;
        }
    }
        
    if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]  && gameBoard[0][2] != ' '){
        if (gameBoard[0][2] == playerSymbol){
            return +10;
        }
        else{
            return -10;
        }
    }
//If no one's won.
    return 0;
}


//Obtain the maximum value that the maximizer or minimizer can obtain, simulating a game between the two until a terminal game state is reached.
int miniMax(std::vector<std::vector<char> > gameBoard, int depth, bool isMaximizer, char playerSymbol){
    int bestScore;
    int score = minimax_score(gameBoard, depth, playerSymbol);
//Indicating a terminal game state.
    if (score == +10){
        return score - depth;
    }
    else if (score == -10){
        return score + depth;
    }
    char computerSymbol;
    if (playerSymbol == 'X'){
        computerSymbol = 'O';
    }
    else{
        computerSymbol = 'X';
    }
    if (isMaximizer){
        bestScore = -100;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
//If the move is available.
                if (gameBoard[i][j] == ' '){
                    gameBoard[i][j] = computerSymbol;
                    bestScore = std::max(bestScore, miniMax(gameBoard, depth + 1, !isMaximizer, playerSymbol));
//Undo the move so it's not permanent.
                    gameBoard[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
    else{
//We're the minimizer now
        bestScore = +100;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (gameBoard[i][j] == ' '){
                    gameBoard[i][j] = playerSymbol;
                    bestScore = std::min(bestScore, miniMax(gameBoard, depth + 1, !isMaximizer, playerSymbol));
                    gameBoard[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

//Take a game state, a computer play symbol, and play the optimal move based on the miniMax algorithm.
std::vector<std::vector<char> > computer_play(std::vector<std::vector<char> > gameBoard, char computerSymbol){
    char playerSymbol;
    int bestRow = 0;
    int bestCol = 0;
    int bestScore = -1000;
    if (computerSymbol == 'X'){
        playerSymbol = 'O';
    }
    else{
        playerSymbol = 'X';
    }
//Find the optimal move to play.
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
//Only evaluate moves that are available.
            if (gameBoard[i][j] == ' '){
                gameBoard[i][j] = playerSymbol;
                int moveScore = miniMax(gameBoard, 0, false, playerSymbol);
                gameBoard[i][j] = ' ';
                if (moveScore > bestScore){
                    bestScore = moveScore;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
//Play that move.
    gameBoard[bestRow][bestCol] = computerSymbol;
    return gameBoard;
}

char get_playerSymbol(){
    while (true){
        std::string msg = "Would you like to play X or O? (X/O): ";
        std::cout << msg;
        char answer;
        std::cin >> answer;
        if (answer == 'X' | answer == 'O'){
//Ask again
            return answer;
        }
    }
}


std::vector<std::vector<char> > play_turn(std::vector<std::vector<char> > gameBoard, char playerSymbol){
    bool moved = false;
    while (not moved){
        std::string rowplaymsg = "Please enter a row to play: ";
        std::cout << rowplaymsg;
        int rowMove;
        std::cin >> rowMove;
        std::string colplaymsg = "Please enter a column to play: ";
        std::cout << colplaymsg;
        int colMove;
        std::cin >> colMove;
        if (gameBoard[rowMove - 1][colMove - 1] != ' '){
            std::cout << "Please move in an empty space\n";
        }
        else{
            gameBoard[rowMove -1][colMove - 1] = playerSymbol;
            moved = true;
            std::cout << "Move confirmed.\n";

        }
    }
    return gameBoard;
}


std::vector<char> check_status(std::vector<std::vector<char> > gameBoard, char playerSymbol, char computerSymbol){
    for (int i = 0; i<3; i++){
        //Checking for a row win.
        if (gameBoard[i][0]==gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] != ' '){
            return {gameBoard[i][0]};
        }
    }
    for (int j = 0; j<3; j++){
        if (gameBoard[0][j]==gameBoard[1][j] && gameBoard[1][j]==gameBoard[2][j] && gameBoard[0][j] != ' '){
            return {gameBoard[0][j]};
        }
    }
    // Checking for Diagonals for X or O victory.
    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1]==gameBoard[2][2] && gameBoard[0][0] != ' '){
        return {gameBoard[0][0]};
    }
    else if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[0][2] != ' '){
        return {gameBoard[0][2]};
    }
    else if (isDraw(gameBoard)){
        return {'D'};
    }
    else{
        return {'N'};
    }
}


int main(){
    std::vector<int> gameStatus;
    std::string winner;
    char playSymbol = get_playerSymbol();
    char computerSymbol;
    if (playSymbol == 'X'){
        computerSymbol = 'O';
    }
    else{
        computerSymbol = 'X';
    }
    std::vector<std::vector<char> > board;
    for (int rowCounter = 0; rowCounter < 3; rowCounter++){
        std::vector<char> row;
        for (int colCounter = 0; colCounter < 3; colCounter++){
            row.push_back(' ');
        }
        board.push_back(row);
    }
    bool playerGoesFirst = true;
    bool gamerunning = true;
    while (gamerunning){
        //Print the status of the game
        if (playerGoesFirst){
            board = play_turn(board, playSymbol);
            printGameStatus(board);
            std::vector<char> status = check_status(board, playSymbol, computerSymbol);
            if (status[0] != 'N'){
                gamerunning = false;
            }
//Only let the computer make a move if the game hasn't ended yet.
            if (gamerunning){
                board = computer_play(board, computerSymbol);
                std::cout << "The computer has moved.\n";
                printGameStatus(board);
            }
        }
        else{
            board = computer_play(board, computerSymbol);
            std::cout << "The computer has moved.\n";
            printGameStatus(board);
            std::vector<char> status = check_status(board, playSymbol, computerSymbol);
            if (status[0] != 'N'){
                gamerunning = false;
            }
//Only let the player make a move if the game hasn't ended yet.
            if (gamerunning){
                board = play_turn(board, playSymbol);
                printGameStatus(board);
            }
        }
        std::vector<char> status = check_status(board, playSymbol, computerSymbol);
        if (status[0] != 'N'){
        gamerunning = false;
        }
    }
//Get the status of the game
    std::vector<char> status = check_status(board, playSymbol, computerSymbol);
    if (status[0] == 'D'){
        std::cout << "Game ended in a draw.\n";
    }
    else{
        std::cout << status[0] << " wins!\n";
    }
}

