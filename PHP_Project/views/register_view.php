<?php include_once "../views/includes/static_view_up.php"; ?>
<div id = "content">
            <h2> Register </h2>
            <?php 
                foreach($register["error"] as $msg) 
                    echo $msg."<br>";
            ?>
            <div>
                <form method = "post"  name = "registerForm" >
                    <label for = "login"> login: </label><br>
                    <input type = "text" name = "login" value = "<?php echo $register['login']; ?>" placeholder = "login.."><br>
                    <label for = "email"> email: </label><br>
                    <input type = "text" name = "email" value = "<?php echo $register['email']; ?>" placeholder = "email.."><br>
                    <label for = "password"> password: </label><br>
                    <input type = "password"  value = "<?php echo $register['password']; ?>" name = "password"><br>
                    <label for = "password"> repeat password: </label><br>
                    <input type = "password"  value = "<?php echo $register['password_repeat']; ?>" name = "password_repeat"><br>
                    <input type = "submit" value="Submit">
                </form>
            </div>
        </div>
<?php include_once "../views/includes/static_view_down.php"; ?>