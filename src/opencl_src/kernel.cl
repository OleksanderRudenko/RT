//
// kernel void kernel_rt(
// 		 size_t figures_num,
// 		 size_t lights_num,
//       __global t_cl_figure *figures,
//       __constant t_cl_light *light,
//       float3 cam_v,
//       float3 cam_o,
//       int antialaising,
//       __global unsigned int *output,
//       int server_client)
// {
//  size_t x = get_global_id(0);
//  size_t y = get_global_id(1);
//  size_t w = get_global_size(0);
//  size_t h = get_global_size(1);
//  unsigned int color;
//  if (server_client == 0){
//  color = do_rt(x, y, w, h,
// 	  figures, light, cam_v, cam_o,
// 	  figures_num, lights_num, antialaising);
// 	  output[y * w + x] = color;}
//  else if (server_client == 1 && y < h / 2){
//  color = do_rt(x, y, w, h,
// 	  figures, light, cam_v, cam_o,
// 	  figures_num, lights_num, antialaising);
// 	  output[y * w + x] = color;}
//  else if (server_client == -1 && y >= h / 2)
//  {
//    color = do_rt(x, y, w, h,
// 	  figures, light, cam_v, cam_o,
// 	  figures_num, lights_num, antialaising);
// 	  output[y * w + x] = color;
//   }
// }


kernel void kernel_rt(
		 	size_t figures_num,
		 size_t lights_num,
      __global t_cl_figure *figures,
      __constant t_cl_light *light,
      float3 cam_v,
      float3 cam_o,
	    int antialaising,
	   __global unsigned int *array,
      __global unsigned int *output,
       int server_client)
 {
		 size_t x = get_global_id(0);
		 size_t y = get_global_id(1);
		 size_t w = get_global_size(0);
		 size_t h = get_global_size(1);
		 unsigned int color;
		 if (server_client == 0)
		 {
				 color = do_rt(x, y, w, h,
			  figures, light, cam_v, cam_o,
			  figures_num, lights_num, antialaising, array);
			  output[y * w + x] = color;
			}
		 else if (server_client == 1 && y < h / 2)
		 {
				 color = do_rt(x, y, w, h,
			  figures, light, cam_v, cam_o,
			  figures_num, lights_num, antialaising, array);
			  output[y * w + x] = color;
			}
		 else if (server_client == -1 && y >= h / 2)
		 {
				 color = do_rt(x, y, w, h,
			  figures, light, cam_v, cam_o,
			  figures_num, lights_num, antialaising, array);
			  output[y * w + x] = color;
			}
	// return (ft_strdup(kernel));
}
