<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    session_start();
    include("./includes/user.php");
    $currUser = new User();
    $currUser->setUser($_POST["user"]);
    $currUser->setPass($_POST["pass"]);
    $currUser->setfName(ucfirst($_POST["fname"]));
    $currUser->setlName(ucfirst($_POST["lname"]));
    $currUser->setAdmin($_POST["admin"]);
    
    $result = $currUser->addToSql();
} else {
    header("Location: ./index.php");
}


//If there is a user with that username already
if ($result == -1){
    //Save error message and send back to register page
    $_SESSION["err"] = "Username already taken";
    header("Location: ./registerform.php");
}
else{
    //If no user with that username, set "err" to account creation confirmation and go back to index
    $_SESSION["err"] = "User Account Created!";
    header("Location: ./index.php");
    
}
