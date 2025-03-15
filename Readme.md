# [vkguide](https://vkguide.dev/)


## chapter1
### Vulkan 初始化
Vulkan不像OpenGL那样允许你几乎立即执行图形指令.
Vulkan需要一个漫长的初始化阶段.我们使用VkBootstrap库简化这个过程, 帮助我们处理这些样板文件.

Vulkan是显式的,提供非常直接的控制. 需要你做加载拓展之类的初始化,选择待使用的GPU, 创建vkInstance和vkDevice结构体, 然后再使用vulkan命令

Vulkan不像OpenGL那样有全局的状态, 因此你需要手动给vkDevice或者VkInstance调用API.
在本教程中,我们链接到vlukan-1.dll去直接访问函数, 但这不是唯一的方式.也可以手动载入函数指针.
连接到vulkan-1.dll不会加载拓展, 还是必须要手动加载拓展.
在项目代码中, Volk库提供加载拓展的办法. 部分教程章节中不会用到, 但是之后会用到,所以依旧提供了.

### VkInstance
代表Vulkan API Context.
单例,一般只会创建一个.

vkbootstrap简化了大量初始化工作, 但是如果不想用它,那么[vulkan-tutorial](https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Instance)会有相关内容

### Swapchain
记得在OpenGL里面最终显示图像时候需要调用SwapChian, 而Vulkan里面有一个swapchain二者应该有什么联系.
Vulkan的swapchain是一系列framebuffer集合,


// 初始化顺序:SDL->VulkanInstance->Surface->Device->Swapchain
// 所以清理顺序相反
// 顺序：Swapchain->Device->Surface->VulkanInstance->SDL