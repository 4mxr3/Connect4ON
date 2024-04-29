        /*
 * Author: Janaye Jackson
 * Created on April 17th 2024 5:54 PM
 * 
 * Connect 4 written in javscript
 */

let spots;
let gOver;
let player;
let comp;
let pMove;
let board;
let row;
let col;
let turn;


var view = {
    displayMessage: function(message){
        var messageArea = document.getElementById("messageArea");
        messageArea.innerHTML = message;
    },
    displayPlayer: function(move, color){
        var cell = document.getElementById(move);
        cell.setAttribute("class", color);
    }
};

//player move
function plaMove(playerNumber, user) {
    let color;
    let move;
    
    if(playerNumber === 1)
        color = "red";
    else
        color = "yellow";
        
        
    pMove = user;

    for (let i = 5; i >= 0; i--) {
        if (board[i][pMove] === 0) {
            move = i +""+ pMove;
            board[i][pMove] = playerNumber;
            view.displayPlayer(move, color);
            break;
        }
    }
    spots++;
    return playerNumber;
}

function AIMove()
{
    let cMove = Math.floor(Math.random() * 3);
    let block = Math.floor(Math.random() *2);
    let success = false;
    let color = "yellow";
    let move;
    
    if(block === 0)
    {
        if(cMove === 0)
        {
            for(let i = 5; i>=0; i--){
                if(board[i][pMove] === 0){
                board[i][pMove] = comp;
                move = i +""+ pMove;
	        view.displayPlayer(move, color);
                success = true;
                break;
                }
            }
        }
        if(cMove === 1 || success === false){
            for(let i = 5; i>=0; i--){
                for(let j = 1; j <= 6 - pMove; j++){
                    if(board[i][pMove + j] === 0){
                        board[i][pMove + j] = comp;
			pMove = pMove + j;
                        move = i +""+ pMove;
                        view.displayPlayer(move, color);
                        success = true;
                        break;
                    }
                }
                if(success)
                    break;
            }
        }
        if(cMove === 2 || success === false){
            console.log("block3");
            for(let i = 5; i>=0; i--){
                for(let j = 6; j >= pMove - j; j--){
                    if(board[i][pMove - j] === 0){
                        board[i][pMove - j] = comp;
			pMove = pMove - j;
                        move = i +""+ pMove;
                        view.displayPlayer(move, color);
                        success = true;
                        break;
                    }
            }
                if(success)
                    break;
            }
        }
    }
    if(block === 1 || success === false){
        do{
            cMove = Math.floor(Math.random() * 7);
            for(let i = 5; i>=0; i--){
                if(board[i][cMove] === 0){
                board[i][cMove] = comp;
                move = i +""+ cMove;
                view.displayPlayer(move, color);
                success = true;
                break;
                }
            }
            
        }while(!success);   
    }
    
    
    view.displayMessage("Player's Turn");
    spots++;
}

function win(turn)
{
    /*
     * win conditions
     * 1. if 0, then reset whole thing
     * 2. if 0 and player = 0, then mark first spot
     * 3. if spot = player, then tally win condtion
     * 4. else not, then switch over to other player filling spot
     */
    //declare and initialize variables
    let count; 
    
    //check row wins
    for (let i = 0; i < row; i++)
    {
        count = 0;
        for (let j = 0; j < col; j++)
        {
            if (board[i][j] === turn)
            {
                count++;
                if (count === 4)
                    return true;
            }
            else
            {
                count = 0; // Reset count if not consecutive
            }
        }
    }

   
    //if no win reset count
    count = 0;
    
    //check column wins
    for (let j = 0; j < col; j++)
    {
        let count = 0;
        for (let i = 0; i < row; i++)
        {
            if (board[i][j] === turn)
            {
                count++;
                if (count === 4)
                    return true;
            }
            else
            {
                count = 0; // Reset count if not consecutive
            }
        }
    }
    
    //if no win reset count
    count = 0;
    
    //for checking diagonal win conditions
    for (let i = 0; i < row - 3; i++)
    {
        for (let j = 0; j < col - 3; j++)
        {
            //diagonals from top-left to bottom-right
            if (board[i][j] === turn &&
                board[i + 1][j + 1] === turn &&
                board[i + 2][j + 2] === turn &&
                board[i + 3][j + 3] === turn)
            {
                return true;
            }

            // diagonals from top-right to bottom-left
            if (board[i][j + 3] === turn &&
                board[i + 1][j + 2] === turn &&
                board[i + 2][j + 1] === turn &&
                board[i + 3][j] === turn)
            {
                return true;
            }
        }
    }
    
    //if no wins at all 
    return false;
}

function playerVsPlayer(user) {
    let gOver;
    let moves = 42;
    
        // Player 1's move
    plaMove(turn, user);
    gOver = win(turn);
    
    if (spots === moves && !gOver) {
        alert("The game ended in a tie");
        //data.updateRecord(gameBoard->game, 3);
        reset();
    }
    if (gOver && turn === 1) {
        alert("Player 1 is the winner");
        //data.updateRecord(gameBoard->game, 1);
        reset();
    } else if (gOver && turn === 2) {
        alert("Player 2 is the winner");
        //data.updateRecord(gameBoard->game, 2);
        reset();
    }
    
    if(turn ===2)
        turn = 1;
    else if(turn === 1)
        turn = 2;
    view.displayMessage("Player " + turn + "'s turn");
}


function playerVsComputer(user){
    let player = 1; // Player 1 starts the game
    let turn;
    let gOver;
    let moves = 42;
    
        // Player's move
        turn = plaMove(player, user);
        gOver = win(turn);

    if (spots >= moves && !gOver) { 
        alert("The game ended in a tie");
        //data.updateRecord(gameBoard->game, 3);
        reset();
    }
    if (gOver && turn === 1) {
        alert("You are the winner");
        //data.updateRecord(gameBoard->game, 1);
        reset();
    } else if(gOver && turn === 2){
        alert("The computer won");
        //data.updateRecord(gameBoard->game, 2);
        reset();
    }
     
        // Computer's move
        turn = AIMove(); 
        gOver = win(turn);

    if (spots >= moves && !gOver) { 
        alert("The game ended in a tie");
        //data.updateRecord(gameBoard->game, 3);
        reset();
    }
    if (gOver && turn === 1) {
        alert("You are the winner");
        //data.updateRecord(gameBoard->game, 1);
        reset();
    } else if(gOver && turn === 2){
        alert("The computer won");
        //data.updateRecord(gameBoard->game, 2);
        reset();
    }
    
}

function game(){
    row = 6;
    col = 7;
    board = [];
    
    for(let i = 0; i < row; i++){
	board.push([0]);
        for(let j = 0; j < col; j++){
            board[i][j] = 0;
        }
    }
    turn = 1;
    comp = 2;
    spots = 0;

   
   do{
     uInput = prompt("Would you like to play \n1. Player vs Player \n2. Player vs Computer");
     uInput = parseInt(uInput);
     if(uInput === 1 || uInput === 2)
         valid = true;
     else{
         alert("Invalid selection, please choose option 1 or 2");
     }
   }while(!valid);
   
    message = "Player 1, please put a legal column(0 to 6, left to right)";
    view.displayMessage(message); 

};

function reset(){
    let choice = prompt("Would you like to play a new game? yes or no");
    if(choice === "yes")
        location.reload();
    else
        window.open("GameOver.html");
}

function handleMove() {
    var userMove = document.getElementById("userMove");
    user = userMove.value;
    if(uInput === 1)
        playerVsPlayer(user);
    else
        playerVsComputer(user);
}

function handleKeyPress(e) {
    var getMove = document.getElementById("getMove");
    if (e.keyCode === 13) {
        getMove.click();
        return false;
    }
   }
   
function init() {
    game();
    var getMove = document.getElementById("getMove");
    getMove.onclick = handleMove;
    var userMove = document.getElementById("userMove");
    userMove.onkeypress = handleKeyPress;
}

window.onload = init;