<?php
require '../../vendor/autoload.php';

function get_db()
{
    $mongo = new MongoDB\Client(
        "mongodb://localhost:27017/wai",
        [
            'username' => 'wai_web',
            'password' => 'w@i_w3b',
        ]);
    $db = $mongo->wai;
    return $db;
}

function look_for_photo($data, $key)
{
    $db = get_db();
    $query = [$key => $data];
    $photo = $db -> photos -> findOne($query);
    return $photo;
}

function look_for_user($data, $key)
{
    $db = get_db();
    $query = [$key => $data];
    $user = $db -> users -> findOne($query);
    return $user;
}

function add_user($new_user)
{
    $db = get_db();
    $hashed_password = password_hash($new_user['password'], PASSWORD_DEFAULT);
    $user = [
        'login' => $new_user['login'],
        'email' => $new_user['email'],
        'hashed_password' => $hashed_password
    ];
    $db -> users -> InsertOne($user);
}

function add_photo($new_photo, $file_name)
{
    if($_FILES['photo']['type'] == 'image/jpeg')
        $extension = ".jpg";
    else
        $extension = ".png";
    $db = get_db();
    $i = "0";
    $file_name = substr($file_name, 0, strrpos($file_name,"."));
    do
    {
        $query = ['file_name' => $file_name.$i++.$extension];
        $old_photo = $db -> photos -> findOne($query);
    }
    while($old_photo != null);
    
    $photo = [
        'file_name' => $file_name.--$i.$extension,
        'title' => $new_photo['title'],
        'author' => $new_photo['author']
    ];
    $db -> photos -> InsertOne($photo);
    return $file_name.$i.$extension;
   
}

function file_size_check($size)
{
    $err = "";
    if($size > 1000000)
        $err = FILE_TOO_BIG_ERROR;
    return $err;
}

function file_type_check($type)
{
    $err = "";
    if($type != 'image/jpeg' && $type != 'image/png')
        $err = FILE_TYPE_ERROR;
    return $err;
}

function create_thumbnail($location, $width, $height, $file_name)
{
    if($_FILES['photo']['type'] == 'image/jpeg')
        $photo = imagecreatefromjpeg($location);
    else
        $photo = imagecreatefrompng($location);
    $thumbnail = imagecreatetruecolor(200, 125);
    imagecopyresampled($thumbnail, $photo, 0, 0, 0, 0, 200, 125, $width, $height);
    if($_FILES['photo']['type'] == 'image/jpeg')
        $photo = imagejpeg($thumbnail, THUMBNAILS_PATH.'/'.$file_name);
    else
        $photo = imagepng($thumbnail, THUMBNAILS_PATH.'/'.$file_name);
}

function create_watermark_photo($location, $file_name)
{
    if($_FILES['photo']['type'] == 'image/jpeg')
        $photo = imagecreatefromjpeg($location);
    else
        $photo = imagecreatefrompng($location);
    $textcolor = imagecolorallocate($photo, 0, 0, 0);
    $font_file = FONT;
    $watermark_text = $_POST['watermark'];
    imagettftext($photo, 20, 0, 30, 30, $textcolor, $font_file,  $watermark_text);
    if($_FILES['photo']['type'] == 'image/jpeg')
        $photo = imagejpeg($photo, PHOTOS_WATERMARK_PATH.'/'.$file_name);
    else
        $photo = imagepng($photo, PHOTOS_WATERMARK_PATH.'/'.$file_name);
}  

function email_check($email)
{
    $err = "";
    if (strlen(trim($email)) == 0)  $err = EMAIL_EMPTY_ERROR;
    elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) 
        $err = EMAIL_FORMAT_ERROR;
    elseif (look_for_user($email, 'email')) 
        $err = EMAIL_ALREADY_EXIST_ERROR;
    return $err;
}

function login_check($login)
{
    $err = "";
    if (strlen(trim($login)) == 0)  $err = LOGIN_EMPTY_ERROR;
    return $err;
}

function password_check($password)
{
    $err = "";
    if (strlen(trim($password)) == 0)  $err = PASSWORD_EMPTY_ERROR;
    return $err;
}

function logging_in_check($login,$password)
{
    $err = "";
    if($user = look_for_user($login, 'login'))
    {
        if(!password_verify($password, $user['hashed_password']))
            $err = LOGGING_IN_ERROR;
    }
    else $err = LOGGING_IN_ERROR;

    return $err;
}

function author_check($author)
{
    $err = "";
    if (strlen(trim($author))==0)  $err = AUTHOR_EMPTY_ERROR;
    return $err;
}

function title_check($title)
{
    $err = "";
    if (strlen(trim($title))==0)  $err = TITLE_EMPTY_ERROR;
    return $err;
}

function watermark_check($watermark)
{
    $err = "";
    if (strlen(trim($watermark))==0)  $err = WATERMARK_EMPTY_ERROR;
    return $err;
}

function error_handling(&$model, $array, $error_check)
{
    if(strlen($error_check) > 0)
        $model[$array]["error"][] = $error_check;
}
?>
