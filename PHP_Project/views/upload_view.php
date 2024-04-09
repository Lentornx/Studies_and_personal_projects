<?php include_once "../views/includes/static_view_up.php"; ?>
        <div id = "content">
            <h2> Upload </h2>
            <?php 
                foreach($upload["error"] as $msg) 
                    echo $msg."<br>";
            ?>
            <div>
                <form method = "post" enctype = "multipart/form-data" name = "uploadForm" >
                    <label for = "author"> author's name: </label><br>
                    <input type = "text" name = "author" value = "<?php echo $upload['author'] ?>" placeholder = "author.."><br>
                    <label for = "title"> photo's title: </label><br>
                    <input type = "text" name = "title" value = "<?php echo $upload['title'] ?>" placeholder = "title.."><br>
                    <label for = "watermark"> watermark: </label><br>
                    <input type = "text" name = "watermark" value = "<?php echo $upload['watermark'] ?>" placeholder = "watermark.."><br>
                    <label for = "file"> upload below: </label><br>
                    <input type = "file" name = 'photo'><br>
                    <input type = "submit" value="Submit">
                </form>
            </div>
        </div>
<?php include_once "../views/includes/static_view_down.php"; ?>