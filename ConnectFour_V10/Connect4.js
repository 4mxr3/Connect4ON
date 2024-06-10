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
    displayMessage: function(message, colorPart){
        var color = (colorPart === 'yellow') ? '#FFD700' : colorPart;
        var messageArea = document.getElementById("messageArea");
        messageArea.innerHTML = message + ` (<span style="color: ${color};">${colorPart}</span>)`;
    },
    displayPlayer: function(move, color){
        var cell = document.getElementById(move);
        cell.setAttribute("class", color);
    }
};

function plaMove(playerNumber, user) {
    let color;
    let move;
    
    if(playerNumber === 1)
        color = "red";
    else
        color = "yellow";
        
    pMove = user - 1;  // Adjusting for 1-based index

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


function AIMove() {
    let cMove = Math.floor(Math.random() * 3);
    let block = Math.floor(Math.random() * 2);
    let success = false;
    let color = "yellow";
    let move;
    
    if (block === 0) {
        if (cMove === 0) {
            for (let i = 5; i >= 0; i--) {
                if (board[i][pMove] === 0) {
                    board[i][pMove] = comp;
                    move = i + "" + pMove;
                    view.displayPlayer(move, color);
                    success = true;
                    break;
                }
            }
        }
        if (cMove === 1 || success === false) {
            for (let i = 5; i >= 0; i--) {
                for (let j = 1; j <= 6 - pMove; j++) {
                    if (board[i][pMove + j] === 0) {
                        board[i][pMove + j] = comp;
                        pMove = pMove + j;
                        move = i + "" + pMove;
                        view.displayPlayer(move, color);
                        success = true;
                        break;
                    }
                }
                if (success) break;
            }
        }
        if (cMove === 2 || success === false) {
            console.log("block3");
            for (let i = 5; i >= 0; i--) {
                for (let j = 6; j >= pMove - j; j--) {
                    if (board[i][pMove - j] === 0) {
                        board[i][pMove - j] = comp;
                        pMove = pMove - j;
                        move = i + "" + pMove;
                        view.displayPlayer(move, color);
                        success = true;
                        break;
                    }
                }
                if (success) break;
            }
        }
    }
    if (block === 1 || success === false) {
        do {
            cMove = Math.floor(Math.random() * 7);
            for (let i = 5; i >= 0; i--) {
                if (board[i][cMove] === 0) {
                    board[i][cMove] = comp;
                    move = i + "" + cMove;
                    view.displayPlayer(move, color);
                    success = true;
                    break;
                }
            }
        } while (!success);
    }
    
    view.displayMessage("Player's Turn", "red");
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
        }
    }

    for(let i = 0; i < row - 3; i++)
    {
        for (let j = 3; j < col; j++)
        {
            // diagonals from top-right to bottom-left
            if (board[i][j] === turn &&
                board[i + 1][j - 1] === turn &&
                board[i + 2][j - 2] === turn &&
                board[i + 3][j - 3] === turn)
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
        reset(3);
    }
    if (gOver && turn === 1) {
        alert("Player 1 is the winner");
        reset(1);
    } else if (gOver && turn === 2) {
        alert("Player 2 is the winner");
        reset(2);
    }
    
    if(turn === 2)
        turn = 1;
    else if(turn === 1)
        turn = 2;
        
    let color = (turn === 1) ? "red" : "yellow";
    view.displayMessage("Player " + turn + ", please put a legal column (1 to 7, left to right)", color);
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
        reset(3);
    }
    if (gOver && turn === 1) {
        alert("You are the winner");
        reset(1);
    } else if(gOver && turn === 2){
        alert("The computer won");
        reset(2);
    }
     
    // Computer's move
    turn = AIMove(); 
    gOver = win(turn);

    if (spots >= moves && !gOver) {
        reset(3);
        alert("The game ended in a tie");
    }
    if (gOver && turn === 1) {
        reset(1);
        alert("You are the winner");
        
    } else if(gOver && turn === 2){
        reset(2);
        alert("The computer won");
    }
    
}

function game() {
    row = 6;
    col = 7;
    board = [];
    
    for (let i = 0; i < row; i++) {
        board.push([0]);
        for (let j = 0; j < col; j++) {
            board[i][j] = 0;
        }
    }
    turn = 1;
    comp = 2;
    spots = 0;
   
    do {
        uInput = prompt("Would you like to play \n1. Player vs Player \n2. Player vs Computer");
        uInput = parseInt(uInput);
        if (uInput === 1 || uInput === 2) valid = true;
        else alert("Invalid selection, please choose option 1 or 2");
    } while (!valid);
   
    view.displayMessage("Player 1, please put a legal column (1 to 7, left to right)", "red"); 
}


function reset(result){
    var prompt = document.getElementById("response");
    prompt.innerHTML += "<input type='hidden' name='result' value='" + parseInt(result) + "'>\n";
    prompt.innerHTML += "<label for='replay'>Would you like to play again?</label><br>\n";
    prompt.innerHTML += "Yes<input type='radio' name='replay' value='1'>\n";
    prompt.innerHTML += "No<input type='radio' name='replay' value='0'> <br>\n";
    prompt.innerHTML += "<input type='submit' value='Submit'>\n";
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