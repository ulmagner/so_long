void	player_image(t_image *player, t_window *window)
{
	player[0].img_path = "./one/user interface/highlight/player1.xpm";
	player[0].img = mlx_xpm_file_to_image(window->mlx, \
		player[0].img_path, &player[0].width, &player[0].height);
	player[0].addr = mlx_get_data_addr(player[0].img, \
		&player[0].bits_per_pixel, &player[0].line_length, &player[0].endian);
}