<?php
// allusers.php

include("./includes/user.php");
session_start();
$_SESSION["loginErr"] = "";
$currUser = new User();
$result = $currUser->fillFromSql($_SESSION["user"], $_SESSION["pass"]);

if ($result == -1) {
    // If not user found, set login error message
    $_SESSION["loginErr"] = "No user with that username and password";
    // Send back to main page
    header("Location: ./index.php");
} elseif (!$currUser->getAdmin()) {
    header("Location: ./displaystats.php");
}
?>

<?php
include("./includes/header.php");
?>
<script src="./includes/displayfunctions.js"></script>

<form action='./edituser.php' method='post' onsubmit="return validateEditForm()">
    <div id="login">

    </div>
</form>

<div id='response'>
    <?php
    // Fill array with all users
    $userAry = [];

    // Connect to database
    require ('./dbconnect.php');

    $query = "SELECT `username`, `password` FROM `entity_user`";

    $statement = $pdo->prepare($query);
    $statement->execute();
    $results = $statement->fetchAll(PDO::FETCH_ASSOC);

    for ($i = 0; $i < count($results); $i++) {
        $userAry[$i] = new User();
        $userAry[$i]->fillFromSql($results[$i]["username"], $results[$i]["password"]);
    }

    // Once all users are gotten, place into table
    if (count($userAry) > 0) {
        echo "<input type='text' id='input' onkeyup='filter()' placeholder='Type to filter by username'>";
        echo "<table id='reportTable'>";
        echo "<tr>";
        echo "<th><button id='tableButton' value='0' onclick='sortTable(this.value,0)' >Username</button></th>";
        echo "<th><button id='tableButton' value='1' onclick='sortTable(this.value,0)' >Password</button></th>";
        echo "<th><button id='tableButton' value='2' onclick='sortTable(this.value,0)' >Real Name</button></th>";
        echo "<th><button id='tableButton' value='3' onclick='sortTable(this.value,1)' >Wins</button></th>";
        echo "<th><button id='tableButton' value='4' onclick='sortTable(this.value,1)' >Losses</button></th>";
        echo "<th><button id='tableButton' value='5' onclick='sortTable(this.value,1)' >Ties</button></th>";
        echo "<th><button id='tableButton' value='6' onclick='sortTable(this.value,1)' >Admin</button></th>";
        echo "<th>Edit</th>";
        echo "<th>Delete</th>";
        echo "</tr>";
        for ($i = 0; $i < count($userAry); $i++) {
            echo "<tr>";
            echo "<td>" . $userAry[$i]->getUser() . "</td>";
            echo "<td>" . $userAry[$i]->getPass() . "</td>";
            echo "<td>" . $userAry[$i]->getfName() . " " . $userAry[$i]->getlName() . "</td>";
            echo "<td>" . $userAry[$i]->getWins() . "</td>";
            echo "<td>" . $userAry[$i]->getLosses() . "</td>";
            echo "<td>" . $userAry[$i]->getTies() . "</td>";
            $a = ($userAry[$i]->getAdmin()) ? "Yes" : "No";
            echo "<td>" . $a . "</td>";

            // Edit Button
            echo "<td>";
            echo "<input type='button' value='Edit' onclick='showEditForm(" . $userAry[$i]->toJSON() . ")'>";
            echo "</td>";
            // Delete Button
            echo "<td>";
            echo "<form action='deluser.php' method='post'>";
            echo "<input type='hidden' id='u' name='u' value='" . $userAry[$i]->getUser() . "'>";
            echo "<input type='hidden' id='p' name='p' value='" . $userAry[$i]->getPass() . "'>";
            echo "<input type='submit' value='Delete'>";
            echo "</form></td>";
            echo "</tr>";
        }
        echo "</table>";
    }
    ?>
</div>

<?php
include("./includes/footer.html");
?>
