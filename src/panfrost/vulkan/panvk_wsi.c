/*
 * Copyright © 2021 Collabora Ltd.
 *
 * Derived from tu_wsi.c:
 * Copyright © 2016 Red Hat
 * Copyright © 2015 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "panvk_private.h"

#include "vk_util.h"
#include "wsi_common.h"

static VKAPI_PTR PFN_vkVoidFunction
panvk_wsi_proc_addr(VkPhysicalDevice physicalDevice, const char *pName)
{
   VK_FROM_HANDLE(panvk_physical_device, pdevice, physicalDevice);
   return vk_instance_get_proc_addr_unchecked(&pdevice->instance->vk, pName);
}

VkResult
panvk_wsi_init(struct panvk_physical_device *physical_device)
{
   VkResult result;

   result = wsi_device_init(&physical_device->wsi_device,
                            panvk_physical_device_to_handle(physical_device),
                            panvk_wsi_proc_addr,
                            &physical_device->instance->vk.alloc,
                            physical_device->master_fd, NULL,
                            false);
   if (result != VK_SUCCESS)
      return result;

   physical_device->wsi_device.supports_modifiers = false;

   return VK_SUCCESS;
}

void
panvk_wsi_finish(struct panvk_physical_device *physical_device)
{
   wsi_device_finish(&physical_device->wsi_device,
                     &physical_device->instance->vk.alloc);
}

void
panvk_DestroySurfaceKHR(VkInstance _instance,
                     VkSurfaceKHR _surface,
                     const VkAllocationCallbacks *pAllocator)
{
   VK_FROM_HANDLE(panvk_instance, instance, _instance);
   ICD_FROM_HANDLE(VkIcdSurfaceBase, surface, _surface);

   vk_free2(&instance->vk.alloc, pAllocator, surface);
}

VkResult
panvk_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice,
                                      uint32_t queueFamilyIndex,
                                      VkSurfaceKHR surface,
                                      VkBool32 *pSupported)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_support(
      &device->wsi_device, queueFamilyIndex, surface, pSupported);
}

VkResult
panvk_GetPhysicalDeviceSurfaceCapabilitiesKHR(
   VkPhysicalDevice physicalDevice,
   VkSurfaceKHR surface,
   VkSurfaceCapabilitiesKHR *pSurfaceCapabilities)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_capabilities(&device->wsi_device, surface,
                                              pSurfaceCapabilities);
}

VkResult
panvk_GetPhysicalDeviceSurfaceCapabilities2KHR(
   VkPhysicalDevice physicalDevice,
   const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
   VkSurfaceCapabilities2KHR *pSurfaceCapabilities)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_capabilities2(
      &device->wsi_device, pSurfaceInfo, pSurfaceCapabilities);
}

VkResult
panvk_GetPhysicalDeviceSurfaceCapabilities2EXT(
   VkPhysicalDevice physicalDevice,
   VkSurfaceKHR surface,
   VkSurfaceCapabilities2EXT *pSurfaceCapabilities)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_capabilities2ext(
      &device->wsi_device, surface, pSurfaceCapabilities);
}

VkResult
panvk_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice,
                                      VkSurfaceKHR surface,
                                      uint32_t *pSurfaceFormatCount,
                                      VkSurfaceFormatKHR *pSurfaceFormats)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_formats(
      &device->wsi_device, surface, pSurfaceFormatCount, pSurfaceFormats);
}

VkResult
panvk_GetPhysicalDeviceSurfaceFormats2KHR(
   VkPhysicalDevice physicalDevice,
   const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
   uint32_t *pSurfaceFormatCount,
   VkSurfaceFormat2KHR *pSurfaceFormats)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_formats2(&device->wsi_device, pSurfaceInfo,
                                          pSurfaceFormatCount,
                                          pSurfaceFormats);
}

VkResult
panvk_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice,
                                           VkSurfaceKHR surface,
                                           uint32_t *pPresentModeCount,
                                           VkPresentModeKHR *pPresentModes)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_surface_present_modes(
      &device->wsi_device, surface, pPresentModeCount, pPresentModes);
}

VkResult
panvk_CreateSwapchainKHR(VkDevice _device,
                      const VkSwapchainCreateInfoKHR *pCreateInfo,
                      const VkAllocationCallbacks *pAllocator,
                      VkSwapchainKHR *pSwapchain)
{
   VK_FROM_HANDLE(panvk_device, device, _device);

   const VkAllocationCallbacks *alloc;
   if (pAllocator)
      alloc = pAllocator;
   else
      alloc = &device->vk.alloc;

   return wsi_common_create_swapchain(&device->physical_device->wsi_device,
                                      panvk_device_to_handle(device),
                                      pCreateInfo, alloc, pSwapchain);
}

void
panvk_DestroySwapchainKHR(VkDevice _device,
                       VkSwapchainKHR swapchain,
                       const VkAllocationCallbacks *pAllocator)
{
   VK_FROM_HANDLE(panvk_device, device, _device);
   const VkAllocationCallbacks *alloc;

   if (pAllocator)
      alloc = pAllocator;
   else
      alloc = &device->vk.alloc;

   wsi_common_destroy_swapchain(_device, swapchain, alloc);
}

VkResult
panvk_GetSwapchainImagesKHR(VkDevice device,
                         VkSwapchainKHR swapchain,
                         uint32_t *pSwapchainImageCount,
                         VkImage *pSwapchainImages)
{
   return wsi_common_get_images(swapchain, pSwapchainImageCount,
                                pSwapchainImages);
}

VkResult
panvk_AcquireNextImageKHR(VkDevice device,
                          VkSwapchainKHR swapchain,
                          uint64_t timeout,
                          VkSemaphore semaphore,
                          VkFence fence,
                          uint32_t *pImageIndex)
{
   VkAcquireNextImageInfoKHR acquire_info = {
      .sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR,
      .swapchain = swapchain,
      .timeout = timeout,
      .semaphore = semaphore,
      .fence = fence,
      .deviceMask = 0,
   };

   return panvk_AcquireNextImage2KHR(device, &acquire_info, pImageIndex);
}

VkResult
panvk_AcquireNextImage2KHR(VkDevice _device,
                           const VkAcquireNextImageInfoKHR *pAcquireInfo,
                           uint32_t *pImageIndex)
{
   VK_FROM_HANDLE(panvk_device, device, _device);
   VK_FROM_HANDLE(panvk_fence, fence, pAcquireInfo->fence);
   VK_FROM_HANDLE(panvk_semaphore, sem, pAcquireInfo->semaphore);
   struct panvk_physical_device *pdevice = device->physical_device;

   VkResult result =
      wsi_common_acquire_next_image2(&pdevice->wsi_device, _device,
                                     pAcquireInfo, pImageIndex);

   /* signal fence/semaphore - image is available immediately */
   if (result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR) {
      panvk_signal_syncobjs(device, fence ? &fence->syncobj : NULL,
                            sem ? &sem->syncobj : NULL);
   }

   return result;
}

VkResult
panvk_QueuePresentKHR(VkQueue _queue, const VkPresentInfoKHR *pPresentInfo)
{
   VK_FROM_HANDLE(panvk_queue, queue, _queue);
   return wsi_common_queue_present(
      &queue->device->physical_device->wsi_device,
      panvk_device_to_handle(queue->device), _queue,
      queue->vk.queue_family_index, pPresentInfo);
}

VkResult
panvk_GetDeviceGroupPresentCapabilitiesKHR(
   VkDevice device, VkDeviceGroupPresentCapabilitiesKHR *pCapabilities)
{
   memset(pCapabilities->presentMask, 0, sizeof(pCapabilities->presentMask));
   pCapabilities->presentMask[0] = 0x1;
   pCapabilities->modes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;

   return VK_SUCCESS;
}

VkResult
panvk_GetDeviceGroupSurfacePresentModesKHR(
   VkDevice device,
   VkSurfaceKHR surface,
   VkDeviceGroupPresentModeFlagsKHR *pModes)
{
   *pModes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;

   return VK_SUCCESS;
}

VkResult
panvk_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice,
                                         VkSurfaceKHR surface,
                                         uint32_t *pRectCount,
                                         VkRect2D *pRects)
{
   VK_FROM_HANDLE(panvk_physical_device, device, physicalDevice);

   return wsi_common_get_present_rectangles(&device->wsi_device, surface,
                                            pRectCount, pRects);
}
