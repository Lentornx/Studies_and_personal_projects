<?php
require_once 'business.php';

function thumbnails_gallery(&$model)
{
    if(!isset($_SESSION['page_num']))
        $_SESSION['page_num'] = 1;
    $start_count =  ($_SESSION['page_num']-1) * THUMBNAILS_PER_PAGE;
    $end_count = $start_count + THUMBNAILS_PER_PAGE;
    $i = 0;
    $array = "thumbnails_gallery";
    $file_names = array_diff(scandir(PHOTOS_PATH),['..','.']);
    foreach($file_names as $file)
    {
        if ($i >= $start_count && $i < $end_count) 
            if($photo = look_for_photo($file, 'file_name'))
            {
                if($_SERVER['REQUEST_METHOD'] === 'POST')
                {
                    if(!isset($_POST['favourite_thumbnails']))
                        $_POST['favourite_thumbnails'] = [];
                    if(in_array(($photo['file_name']),$_POST['favourite_thumbnails']) == true)
                        $_SESSION['in_favourites'][$photo['file_name']] = true;
                    else
                        $_SESSION['in_favourites'][$photo['file_name']] = false;
                }
                if(!isset($_SESSION['in_favourites'][$photo['file_name']]))
                    $_SESSION['in_favourites'][$photo['file_name']] = false;
                $photo['in_favourites'] = $_SESSION['in_favourites'][$photo['file_name']];
                $model[$array][] = $photo;
            }
        $i++;
        if ($i == $end_count)
            break;
    }
    if(isset($_SESSION['logged_in_user_login']))
        $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
    else 
        $model["gallery"]["logged_in_user_login"] = null;
    $model["gallery"]["page_id"] = $_SESSION['page_num'];
    $model["gallery"]["scrollbar_count"] = (count($file_names)/THUMBNAILS_PER_PAGE)+((count($file_names))%THUMBNAILS_PER_PAGE ? 1:0);
    return 'thumbnails_gallery_view';
}

function thumbnails_subgallery(&$model)
{
    $_SESSION['page_num'] = $_GET['id'];
    return thumbnails_gallery($model);
}

function fav_thumbnails_gallery(&$model)
{
    if(!isset($_SESSION['fav_page_num']))
        $_SESSION['fav_page_num'] = 1;
    $start_count =  ($_SESSION['fav_page_num']-1) * THUMBNAILS_PER_PAGE;
    $end_count = $start_count + THUMBNAILS_PER_PAGE;    
    $i = 0; 
    $array = "fav_thumbnails_gallery";
    foreach($_SESSION['in_favourites'] as $file => $in_favourites)
    {
        if ($i >= $start_count && $i < $end_count) 
            if($photo = look_for_photo($file, 'file_name'))
            {
                if($_SERVER['REQUEST_METHOD'] === 'POST') // usuwanie z favourite
                {
                    if(!isset($_POST['deleted_from_fav']))
                        $_POST['deleted_from_fav'] = [];
                    if(in_array($file,$_POST['deleted_from_fav']) == true) {
                        $_SESSION['in_favourites'][$file] = false;
                        $in_favourites = false;
                    }
                }
                if($in_favourites === true)
                {
                    $model[$array][] = $photo;
                } 
            } 
        if($in_favourites === true) $i++;       
    }
    $file_num = $i;
    if ($start_count >= $file_num)  
    {
        --$_SESSION['fav_page_num'];
        return fav_thumbnails_gallery($model);
    }
    else
    {
        if(isset($_SESSION['logged_in_user_login']))
            $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
        else 
            $model["gallery"]["logged_in_user_login"] = null;
        $model["gallery"]["fav_page_id"] = $_SESSION['fav_page_num'];
        
        $model["gallery"]["fav_scrollbar_count"] = ($file_num/THUMBNAILS_PER_PAGE)+(($file_num)%THUMBNAILS_PER_PAGE ? 1:0);
        return 'fav_thumbnails_gallery_view';
    }
    
}

function fav_thumbnails_subgallery(&$model)
{
    $_SESSION['fav_page_num'] = $_GET['id'];
    return fav_thumbnails_gallery($model);
}

function upload(&$model)
{
    $array = "upload";
    $model[$array] = [
        'author' => '',
        'title' => '',
        'watermark' => '',
        'error' => []              
    ];
    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {  
            $model[$array]=[
                'author' => isset($_POST['author']) ? $_POST['author']:"",
                'title' => isset($_POST['title']) ? $_POST['title']:"",
                'watermark' => isset($_POST['watermark']) ? $_POST['watermark']:"",
            ];
            $file_name = $_FILES['photo']['name'];
            error_handling($model, $array, author_check($_POST['author']));
            error_handling($model, $array, title_check($_POST['title']));
            error_handling($model, $array, watermark_check($_POST['watermark']));
            error_handling($model, $array, file_size_check($_FILES['photo']['size']));
            error_handling($model, $array, file_type_check($_FILES['photo']['type']));

            if (empty($model[$array]["error"])) 
            {
                //dodawanie tytulu i autora do bazy danych
                $file_name = add_photo($model[$array], $file_name);
                $location = PHOTOS_PATH."/".$file_name;               
                //dodawanie zdjecia do folderu
                move_uploaded_file($_FILES['photo']['tmp_name'], $location);
                list($width, $height) = getimagesize($location);

                create_thumbnail($location, $width, $height, $file_name);
                create_watermark_photo($location, $file_name);
                
                $model["gallery"]["message"] = UPLOAD_SUCCESSFUL;
                if(isset($_SESSION['logged_in_user_login']))
                    $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
                else 
                    $model["gallery"]["logged_in_user_login"] = null;
                return thumbnails_gallery($model);
            }
    }
    return "upload_view";
}

function register(&$model)
{
    $array = "register";
    $model[$array]=[
        'login' => '',
        'email' => '',
        'password' => '',
        'password_repeat' => '',
        'error' => []              
    ];
    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {
            $model[$array]=[
                'login' => isset($_POST['login']) ? $_POST['login']:"",
                'email' => isset($_POST['email']) ? $_POST['email']:"",
                'password' => isset($_POST['password']) ? $_POST['password']:"",
                'password_repeat' => isset($_POST['password_repeat']) ? $_POST['password_repeat']:""                 
            ];
            
            error_handling($model, $array, login_check($_POST['login']));
            error_handling($model, $array, email_check($_POST['email']));
            error_handling($model, $array, password_check($_POST['password']));
            if ($_POST['password_repeat'] !== $_POST['password'] )
                $model[$array]["error"][] = PASSWORD_REPETITION_ERROR;
            elseif (look_for_user($model[$array]['login'], 'login'))
                $model[$array]["error"][] = LOGIN_ALREADY_EXIST_ERROR;
            if (empty($model[$array]["error"])) 
            {
                add_user($model[$array]);
                $_SESSION['logged_in_user_login'] = $_POST['login'];
                $model["gallery"]["message"] = REGISTER_SUCCESSFUL;
                $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
                return thumbnails_gallery($model);
            }
    }
    return "register_view";
}

function login(&$model)
{
    $array = "login";
    $model[$array]=[
        'login' => '',
        'password' => '',
        'error' => []              
    ];
    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {
            $model[$array] = [
                'login' => isset($_POST['login']) ? $_POST['login']:"",
                'password' => isset($_POST['password']) ? $_POST['password']:""
            ];
            
            error_handling($model, $array, login_check($_POST['login']));
            error_handling($model, $array, password_check($_POST['password']));
            error_handling($model, $array, logging_in_check($_POST['login'],$_POST['password']));

            if (empty($model[$array]["error"])) 
            {
                $_SESSION['logged_in_user_login'] = $_POST['login'];
                $model["gallery"]["message"] = LOGIN_SUCCESSFUL;
                $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
                return thumbnails_gallery($model);
            }
    }
    return "login_view";
}

function logout(&$model)
{
    $_SESSION['logged_in_user_login'] = null;
    $model["gallery"]["message"] = LOGOUT_SUCCESSFUL;
    $model["gallery"]["logged_in_user_login"] = $_SESSION['logged_in_user_login'];
    //$db = get_db();  
    //$query = [];
    //$db -> users -> deleteMany($query);
    return thumbnails_gallery($model);
}