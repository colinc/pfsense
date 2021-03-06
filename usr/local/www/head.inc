<?php
/*
	pfSense_MODULE:	header
*/

/* 
 *   if user has selected a custom template, use it.
 *   otherwise default to pfsense tempalte
 */
if (($g["disablethemeselection"] === true) && !empty($g["default_theme"]) && (is_dir($g["www_path"].'/themes/'.$g["default_theme"])))
	$g['theme'] = $g["default_theme"];
elseif($config['theme'] <> "" && (is_dir($g["www_path"].'/themes/'.$config['theme'])))
	$g['theme'] = $config['theme'];
else
	$g['theme'] = "pfsense";

/*
 *  If this device is an apple ipod/iphone
 *  switch the theme to one that works with it.
 */
$lowres_ua = array("iPhone", "iPod", "iPad", "Android", "BlackBerry", "Opera Mini", "Opera Mobi");
foreach($lowres_ua as $useragent)
	if(strstr($_SERVER['HTTP_USER_AGENT'], $useragent))
		$g['theme'] = empty($g['theme_lowres']) ? "pfsense" : $g['theme_lowres'];

$pagetitle = gentitle( $pgtitle );

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title><?php echo($config['system']['hostname'] . "." . $config['system']['domain'] . " - " . $pagetitle); ?></title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<link rel="apple-touch-icon" href="/themes/<?php echo $g['theme']; ?>/apple-touch-icon.png"/>
        <?php if (strpos($_SERVER["SCRIPT_FILENAME"], "wizard.php") !== false &&
                  file_exists("{$g['www_path']}/themes/{$g['theme']}/wizard.css")): ?>
					<?php echo "<style type=\"text/css\" src=\"/themes/{$g['theme']}/wizard.css\"></style>"; ?>
        <?php else: ?>
        	<link rel="stylesheet" href="/themes/<?php echo $g['theme']; ?>/all.css" media="all" />
        <?php endif; ?>
		<link rel="stylesheet" type="text/css" href="/niftycssCode.css">
		<link rel="stylesheet" type="text/css" href="/niftycssprintCode.css" media="print">
		<link rel="stylesheet" type="text/css" href="/themes/<?=$g['theme']?>/new_tab_menu.css" media="all">
		<script type="text/javascript" src="/javascript/niftyjsCode.js"></script>
		<script type="text/javascript" src="/javascript/jquery.js"></script>
		<script type="text/javascript" src="/javascript/jquery/jquery-ui.custom.min.js"></script>
		<script type="text/javascript">
			var theme = "<?php echo $g['theme']; ?>";

			jQuery.noConflict();
		</script>
		<?php echo "\t<script type=\"text/javascript\" src=\"/themes/{$g['theme']}/loader.js\"></script>\n"; ?>
<?php
		if($_GET['enablefirebuglite']) {
			echo "\t<script type=\"text/javascript\" src=\"/javascript/pi.js\"></script>\n";
			echo "\t<script type=\"text/javascript\" src=\"/javascript/firebug-lite.js\"></script>\n";
		}
		echo "\t<script type=\"text/javascript\" src=\"/javascript/scriptaculous/prototype.js\"></script>\n";
		echo "\t<script type=\"text/javascript\" src=\"/javascript/scriptaculous/scriptaculous.js\"></script>\n";
		echo "\t<script type=\"text/javascript\" src=\"/javascript/scriptaculous/effects.js\"></script>\n";
		echo "\t<script type=\"text/javascript\" src=\"/javascript/scriptaculous/dragdrop.js\"></script>\n";
		if(file_exists("{$g['www_path']}/javascript/global.js"))
			echo "\t<script type=\"text/javascript\" src=\"/javascript/global.js\"></script>\n";
	/*
	 *	Find all javascript files that need to be included
	 *	for this page ... from the arrays ... :)
	 *	Coded by: Erik Kristensen
	 */

	$dir  = trim(basename($_SERVER["SCRIPT_FILENAME"], '.php'));
	$path = "{$g['www_path']}/javascript/" . $dir . "/";
	if (is_dir($path)) {
		if ($dh = opendir($path)) {
			while (($file = readdir($dh)) !== false) {
		   		if (is_dir($file)) 
					continue;
				echo "\t<script type=\"text/javascript\" src=\"/javascript/{$dir}/{$file}\"></script>\n";
			}
			closedir($dh);
		}
	}

if (!isset($closehead))
	echo "</head>";

/*  If this page is being remotely managed then do not allow the loading of the contents. */
if($config['remote_managed_pages']['item']) {
	foreach($config['remote_managed_pages']['item'] as $rmp) {
		if($rmp == $_SERVER['SCRIPT_NAME']) {
			include("fbegin.inc");
			print_info_box_np("This page is currently being managed by a remote machine.");
			include("fend.inc");
			exit;
		}
	}	
}

?>
