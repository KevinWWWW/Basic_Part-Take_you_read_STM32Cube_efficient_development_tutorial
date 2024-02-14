### STM32CubeMX 主要更新日志与官网下载直链（Windows版）

- 更新日志翻译自 `https://www.st.com/resource/en/release_note/rn0094-stm32cubemx-release-6100-stmicroelectronics.pdf`
##### 6.10.0
更新于2023年11月22日

主要更新日志：
- 增加了对STM32CubeMP13的支持： STM32MP13xx微处理器的裸机固件
- 增加了对STM32WBA系列中新微控制器的支持
- 增加了对与STM32WBA系列相关的两块新板的支持：NUCLEO-WBA55CG和STM32WBA55G-DK1
- 增加了对与STM32U5系列相关的一块新板的支持：STEVAL-MKBOXPRO
- 增加了对STM32WB系列和STM32WBA系列内存管理工具的支持
- 增加了对新启动的支持：STiRoT Dual
- 增加了对STM32H5系列的makefile工具链的支持
- 增加了在没有管理权限的情况下安装STM32CubeMX的可能性
- 增加了从板开始的新功能
- 将JDK11从Adoptia™Temurin™17.0.6升级到版本17.0.8.1

固件库版本更新：
- STM32F4 V1.28.0
- 【新系列】STM32MP13 V1.0.0
- STM32U5 V1.4.0
- STM32WBA V1.2.0
- STM32WB V1.18.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/d7/f0/6a/65/f9/28/4d/31/stm32cubemx-win-v6-10-0/files/stm32cubemx-win-v6-10-0.zip/jcr:content/translations/en.stm32cubemx-win-v6-10-0.zip`

##### version 6.9.2 
更新于2023年9月5日

主要更新日志：
- 当使用STM32CubeIDE重新生成代码时，安全管理器的链接器文件中给出了错误的RAM位置。
- 当用户创建一个新项目并设置所有设置安全管理器引导路径、启用RTC并生成代码时，整个功能SystemClock_config将从生成的代码中删除。
- 在安全管理器上下文中，当用户通过中间件和软件包部分中的SECURE_MANAGER_API启用PSA API时，STM32CubeMX不会将所有需要的文件复制到Middlewares\ST\secure_manager_api\接口中。即使这些文件后来被手动添加，它们也会在下一次代码生成时被删除。
- 安全管理器构建后cmd不会生成. bin加密文件

固件库版本更新：
- STM32H5 V1.1.1
- STM32WB V1.17.2

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/79/e6/3a/f1/b3/cc/4d/f3/stm32cubemx-win-v6-9-2/files/stm32cubemx-win-v6-9-2.zip/jcr:content/translations/en.stm32cubemx-win-v6-9-2.zip`

##### version 6.9.1
更新于2023年7月28日
主要更新日志：
- 为MDK-ARM重新生成项目时，用户的所有文件和文件夹都将被删除。STM32CubeMX不保留MDK-ARM项目中的用户修改。
- 下载最新版本的X-CUBE-FREERTOS，加载项目，然后编译它会导致编译错误。一些生成的临时文件是问题的根源

固件库版本更新：
- 无

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/09/f7/7c/30/53/50/44/f1/stm32cubemx-win-v6-9-1/files/stm32cubemx-win-v6-9-1.zip/jcr:content/translations/en.stm32cubemx-win-v6-9-1.zip`

##### version 6.9.0 
更新于2023年7月8日
主要更新日志：
- 增加了对STM32U5系列中新微控制器的支持
- 增加了对STM32WBA系列中新微控制器的支持
- 增加了对与STM32U5系列相关的两块新板的支持： STM32U5G9J-DK1和STM32U5G9J-DK2
- 增加了对与STM32L4+系列相关的一块新板的支持：STEVAL-SMARTAG2
- 增加了对STM32H5和STM32U5系列内存管理工具的支持
- 增加了对STM32H5系列新引导路径的支持
- 增加了STM32H7、STM32L5和STM32U5系列双上下文中的makefile生成在STM32U5和STM32WL系列的示例选择器（Example selector）中
- 增加了分层项目支持增加了用户身份验证功能
- 增加了对代码生成前后处理的支持
- 将JDK11升级到Adoptia™Temurin™17.0.6

固件库版本更新：
- STM32C0 V1.1.0
- STM32F1 V1.8.5
- STM32F2 V1.9.4
- STM32H5 V1.1.0
- STM32L4/L4+ V1.18.0
- STM32U5 V1.3.0
- STM32WBA V1.1.0
- STM32WB V1.17.0


官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/ba/fb/2c/71/98/3f/4f/0e/stm32cubemx-win-v6-9-0/files/stm32cubemx-win-v6-9-0.zip/jcr:content/translations/en.stm32cubemx-win-v6-9-0.zip`

##### version 6.8.1
更新于2023年5月3日
主要更新日志：
- 创建ETH项目时，某些变量可能不会生成。补丁修复了它。
- 旧产品（如STM32F7或STM32L0）中的VOSRDY标志与新产品（如STM32H7、STM32U5或STM32H5）中的逻辑不同。补丁修复了代码生成行为，使其在所有情况下都能正常工作。
- LL_PWR_IsActiveFlag_VOS() 在PLL激活时错误生成。这会将调试器推入无限循环。补丁确保正确生成VOS标志，因为VOS标志访问取决于PLL激活。
- -STM32CubeMX V6.8.0在基于任何STM32H7微控制器创建新项目并调整MDMA模式和配置视图大小时崩溃

固件库版本更新：
- 无

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/56/f8/37/0b/1a/b8/44/f5/stm32cubemx-win-v6-8-1/files/stm32cubemx-win-v6-8-1.zip/jcr:content/translations/en.stm32cubemx-win-v6-8-1.zip`

##### version 6.8.0
更新于2023年3月5日
主要更新日志：
- 增加了对STM32H5系列微控制器的支持
- 增加了对STM32U5系列中新微控制器的支持
- 增加了对STM32WBA系列微控制器的支持
- 增加了对与STM32G4系列相关的一块新板的支持： B-G473E-ZEST1S
- 增加了对与STM32H5系列相关的三块新板的支持：NUCLEO-H563ZI、NUCLEO-H503RB、STM32H573I-DK
- 增加了对与STM32U5系列相关的三块新板的支持：STM32U5A9J-DK、NUCLEO-U5A5ZJ-Q、NUCLEO-U545RE-Q
- 增加了对与STM32WBA系列相关的一块新板的支持：NUCLEO-WBA52CG
- 增加了对STM32U5系列中新微控制器的LPBAM支持
- 增加了对Log4j版本的支持STM32L5系列的Azure®RTOS USBX或通用串行总线和通用串行总线之间的共存，使得从通用串行总线中间件启用和禁用通用串行总线支持成
- 为可能为STM32H5系列添加了引导路径配置支持在STM32CubeMX外部工具面板中添加了STM32CubeCLT命令行工具集默认启用数据分析收集
- 将JDK11升级到Adoptia™Temurin™

固件库版本更新：
- STM32C0 V1.0.1
- STM32F0 V1.11.4
- STM32F3 V1.11.4
- 【新系列】STM32H5 V1.0.0
- STM32L0 V1.12.2
- STM32L1 V1.10.4
- STM32U5 V1.2.0
- 【新系列】STM32WBA V1.0.0
- STM32WB V1.16.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/14/7b/7a/22/99/88/4c/d0/stm32cubemx-win-6-8-0/files/stm32cubemx-win-6-8-0.zip/jcr:content/translations/en.stm32cubemx-win-6-8-0.zip`

##### version 6.7.0
更新于2022年11月25日
主要更新日志：
- 添加了对STM32WL系列中一个新产品的支持： STM32WL5MOC
- 添加了对与STM32WB系列相关的一个新板的支持：STEVAL-PROTEUS1
- 添加了对与STM32F0系列相关的一个板的支持：STM320518-EVAL
- 在包创建器中添加了一个菜单来生成包示例描述文件
- 添加了对STM32L5系列Azure®RTOS USBX或USB和USB-PD之间共存的支持，使得从USB-PD中间件启用和禁用USB支持成为可能
- 添加了MCU和板文档的下载在导出到Excel功能中
- 添加了对AI过滤器参数的支持添加了LPBAM的新功能，例如顺序链接队列的可能性
- 将JDK11升级到Adoptia™Temurin™11.0.16

固件库版本更新：
- STM32F4 V1.27.1
- STM32G0 V1.6.1
- STM32G4 V1.5.1
- STM32H7 V1.11.0
- STM32L5 V1.5.0
- STM32WB V1.15.0
- STM32WL V1.3.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/f4/29/83/a4/40/d8/43/43/stm32cubemx-win_v6-7-0/files/stm32cubemx-win_v6-7-0.zip/jcr:content/translations/en.stm32cubemx-win_v6-7-0.zip`

##### version 6.6.1
更新于2022年7月6日
主要更新日志：
- 修复V6.6.0版本中发现的主要问题的补丁版本（请参阅表17）。项目迁移到V6.6.0后，可能会从STM32CubeMX项目中删除一些文件。此补丁版本通过修复这些问题来解决这些问题。

固件库版本更新：
- 无

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/14/64/0d/4f/5b/ec/4d/82/stm32cubemx-win_v6-6-1/files/stm32cubemx-win_v6-6-1.zip/jcr:content/translations/en.stm32cubemx-win_v6-6-1.zip`

##### version 6.6.0
更新于2022年6月29日
主要更新日志：
- 增加了对新STM32MP131、STM32MP133和STM32MP135微处理器的支持： STM32MP131（A-C-D-F）AEx、STM32MP131（A-D-F）AFx、STM32MP131（A-D-F）AGx、STM32MP133（A-C-D-F）AEx、STM32MP133（A-C-D-F）AFx、STM32MP133（A-C-D-F）AGx、STM32MP135（A-C-D-F）AEx、STM32MP135（A-D-F）AFx和STM32MP135（A-C-D-F）AGx。
- 添加了对与STM32MP1系列相关的一个新板的支持：STM32MP135F-DK。
- 添加了对STM32L4系列中一个新零件号的支持：STM32L476VGYxP。
- 添加了搜索功能，以帮助设置MCU、MPU、板和示例为STM32U575/585产品线中带有Arm®TrustZone®（TZEN=1）的项目添加了对LPBAM固件的支持。
- 添加了对与STM32WB系列相关的两个新板的支持： STEVAL-ASTRA1B和B-WB1M-WPAN1。
- 添加了对与STM32U5系列相关的一个新板的支持：STEVAL-STWINBX1。
- 从STM32CubeMX中支持的IDE列表中删除了TrueSTUDIO、SW4STM32 和GPDSC选项

固件库版本更新：
- STM32F7 V1.17.0
- STM32G0 V1.6.0
- STM32L4/L4+ V1.17.2
- STM32MP1 V1.6.0
- STM32U5 V1.1.1
- STM32WB V1.14.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/d2/52/cf/7a/8b/dd/48/df/stm32cubemx-win_v6-6-0/files/stm32cubemx-win_v6-6-0..zip/jcr:content/translations/en.stm32cubemx-win_v6-6-0..zip`

##### version 6.5.0
更新于2022年3月3日
主要更新日志：
- 增加了对STM32U5系列新零件号的支持： STM32U599NJHxQ、STM32U599BJYxQ、STM32U595ZJTxQ、STM32U5A9NJHxQ、STM32U5A9BJYxQ、STM32U5A5ZJTxQ和STM32U599NIHxQ。
- 添加了对STM32C0系列新零件号的支持：STM32C011D6Yx、STM32C011F（4-6）Px、STM32C011F（4-6）Ux、STM32C011J（4-6）Mx、STM32C031C（4-6）Tx、STM32C031C（4-6）Ux、STM32C031K（4-6）Tx、STM32C031K（4-6）Ux、STM32C031G（4-6）Ux和STM32C031F（4-6）Px。
- 添加了对STM32F7系列中两个新零件号的支持： STM32F723VCYxTR和STM32F723VEYxTR。
- 添加了对P-L496G-CELL01和P-L496G-CELL02 Discovery 套件的支持。
- 添加了按类别组织的搜索标准的增强功能，具有更准确的商业产品信息和更具体的留档。
- 为STM32U575/585产品线中没有Arm®TrustZone®（TZEN=0）的项目添加了对LPBAM固件的支持。这一新功能允许基于强大的低功耗项目的轻松设计添加了EWARM编译器版本v8.50的支持。该版本成为STM32F7系列、STM32F4系列、STM32G0系列、STM32G4系列、STM32H7系列、STM32U5系列和STM32C0系列的默认EWARM工具链版本。
- 添加了对Azure®RTOS中间件裸机模式的支持：
- STM32C0系列和STM32U5系列的Azure®RTOS FileX
- STM32U5系列的Azure®RTOS LevelX

固件库版本更新：
- 【新系列】STM32C0 V1.0.0
- STM32F4 V1.27.0
- STM32F7 V1.16.2
- STM32H7 V1.10.0
- STM32L4/L4+ V1.17.1
- STM32U5 V1.1.0
- STM32WB V1.13.1
- STM32WL V1.2.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/dd/bb/c8/34/20/73/45/86/stm32cubemx-win_v6-5-0/files/stm32cubemx-win_v6-5-0.zip/jcr:content/translations/en.stm32cubemx-win_v6-5-0.zip`

##### version 6.4.0
更新于2022年11月23日
主要更新日志：
- 增加了对STM32L4系列和STM32L4+系列中新零件号的支持：STM32L443CCFx、STM32L452CETxP、STM32L452REYxP、STM32L476QGIxP、STM32L496QGIxS、STM32L4R5AIIxP、STM32L4R5QGIxS、STM32L4R5QIIxP和STM32L4P5QGIxS
- 增强了对STM32U5系列和STM32G0系列的Azure®RTOS USBX或USB与USB-PD之间共存的支持，使得启用和禁用USB-PD中间件的USB支持成为可能

固件库版本更新：
- STM32F0 V1.11.3
- STM32F3 V1.11.3
- STM32F4 V1.26.2
- STM32G4 V1.5.0
- STM32L0 V1.12.1
- STM32MP1 V1.5.0
- STM32U5 V1.0.2
- STM32WB V1.13.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/ab/3d/8f/2c/b2/0e/4f/68/stm32cubemx-win/files/stm32cubemx-win.zip/jcr:content/translations/en.stm32cubemx-win.zip`

##### version 6.3.0
更新于2021年7月6日
主要更新日志：
- 在STM32U5系列中添加了对新零件编号的支持：STM32U575A（G-I）Ix, STM32U575A(G-I)IxQ, STM32U575C(G-I)Tx, STM32U575C(G-I)TxQ, STM32U575C(G-I)Ux, STM32U575C(G-I)UxQ, STM32U575O(G-I)YxQ, STM32U575Q(G-I)Ix, STM32U575Q(G-I)IxQ, STM32U575R(G-I)Tx, STM32U575R(G-I)TxQ, STM32U575V(G-I)Tx, STM32U575V(G-I)TxQ, STM32U575Z(G-I)Tx, STM32U575Z(G-I)TxQ, STM32U585AIIx, STM32U585AIIxQ, STM32U585CITx, STM32U585CITxQ, STM32U585CIUx, STM32U585CIUxQ, STM32U585OIYxQ, STM32U585QIIx, STM32U585QEIxQ, STM32U585RITx, STM32U585RITxQ, STM32U585VITx, STM32U585VITxQ, STM32U585ZITx and STM32U585ZETxQ
- 增加了对与STM32U5系列相关的三块新板的支持： B-U585I-IOT02A、NUCLEO-U575ZI-Q和STM32U575I-EV
- 增加了对与STM32MP1系列相关的两块新板的支持：STM32MP157D-DK1和STM32MP157D-EV1
- 增加了对与STM32L4系列相关的一块新板的支持：STEVAL-STWINKT1B
- 增加了对STM32G0系列、STM32WL系列和STM32WB系列的SMBUS快速模式加号和SMBUS快速模式的支持
- 在STM32H7系列中增加了对RAMECC的支持
- 在Arm®TrustZone®激活项目中增加了对STM32L5系列压水堆安全配置的支持（TZEN=1）
- 使用JRE™捆绑支持添加了安装过程的更新。捆绑的JRE™更新为AdoptOpenJDK-11.0.10+9和JavaFX-11.0.2
- 添加了对使用https协议的STM32CubeMX更新的支持
- 添加了许可证点击：用户可以在任何下载之前接受固件包许可证条款添加了线程安全锁定支持。它可以在Project manager>Project线程安全设置中启用或禁用
- 为STM32U5系列和STM32G0系列添加了Azure®RTOS USBX或USB与USB-PD之间的共存支持，使得从USB-PD中间件STM32WB V1.13.0 STM32WL V1.1.0启用和禁用USB支持成为可能

固件库版本更新：
- STM32F1 V1.8.4
- STM32F2 V1.9.3
- STM32F4 V1.26.1
- STM32F7 V1.16.1
- STM32G0 V1.5.0
- STM32L1 V1.10.3
- 【新系列】STM32U5 V1.0.0
- STM32WB V1.12.0
- STM32WL V1.1.0


官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/89/bf/76/a5/35/8e/46/09/stm32cubemx-win_v6-3-0/files/stm32cubemx-win_v6-3-0.zip/jcr:content/translations/en.stm32cubemx-win_v6-3-0.zip`

##### version 6.2.1
更新于2021年3月26日
主要更新日志：
- 在STM32MP1系列中添加了对新固件和清单版本的支持：Linux内核5.10 LTS openstlinux-5.10-dunfel-mp1-21-03-31

固件库版本更新：
- STM32F7 V1.16.1
- STM32G0 V1.4.1
- STM32MP1 V1.4.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/8f/a9/63/5f/b5/23/43/d3/stm32cubemx-win_v6-2-1/files/stm32cubemx-win_v6-2-1.zip/jcr:content/translations/en.stm32cubemx-win_v6-2-1.zip`

##### version 6.2.0
更新于2021年2月23日
主要更新日志：
- 通过安全上下文支持等增强了软件包功能增加了中国大陆居民可访问的新视频
- 增加了对STM32G0系列新零件号的支持：STM32G050C（6-8）Tx、STM32G050F6Px、STM32G050K（6-8）Tx，STM32G051C(6-8)Tx, STM32G051C(6-8)Ux, STM32G051F(6-8)Px, STM32G051F8Yx, STM32G051G(6-8)Ux, STM32G051K(6-8)Tx, STM32G051K(6-8)Ux, STM32G061C(6-8)Tx, STM32G061C(6-8)Ux, STM32G061F(6-8)Px, STM32G061F8Yx, STM32G061G(6-8)Ux, STM32G061K(6-8)Tx, STM32G061K(6-8)Ux, STM32G0B1C(B-C-E)Tx, STM32G0B1C(B-C-E)TxN, STM32G0B1C(B-C)Ux, STM32G0B1C(B-C-E)UxN, STM32G0B1KBTx, STM32G0B1KBTxN, STM32G0B1KBUx, STM32G0B1KBUxN, STM32G0B1MBTx, STM32G0B1NEYx, STM32G0B1R(B-C-E)IxN, STM32G0B1R(B-C-E)Tx, STM32G0B1R(B-C-E)TxN, STM32G0B1VBIx, STM32G0B1VBTx, STM32G0C1C(C-E)TxN, STM32G0C1C(C-E)UxN, STM32G0C1NEYx, STM32G0C1R(C-E)IxN, STM32G0C1R(C-E)Tx, STM32G0C1R(C-E)TxN
- 增加了对STM32L4+系列中新零件号的支持： STM32L4Q5AGIxP、STM32L4Q5CGTx、STM32L4Q5CGTxP、STM32L4Q5CGUx、STM32L4Q5CGUxP、STM32L4Q5QGIx、STM32L4Q5QGIxP、STM32L4Q5RGTxP、STM32L4Q5VGTxP、STM32L4Q5VGYxP、STM32L4Q5ZGTxP
- 增加了对STM32WB系列中新零件号的支持：STM32WB10CCUx、STM32WB15CCUx、STM32WB15CCUxE、STM32WB15CCYx、STM32WB30CEUxA、STM32WB35C（C-E）UxA
- 在STM32G471xxxx零件号中添加了对Q-SPI的支持。
- 添加了对与STMWB系列相关的两个新板的支持： STM32WB5MM-DK和NUCLEO-WB15CC
- 添加了对STM32F4系列新功能的支持：-SMBUS支持-快速模式和快速模式加支持
- 添加了对STM32L4系列、STM32F4系列、STM32L0系列和STM32L5系列的SMBUS快速模式加支持
- 添加了对STM32L5系列中ICACHE LL的支持
- 为STM32WB系列中的ZigBee®添加了功能改进，例如集群回调选择和集群分配的特定参数配置向示例选择器
- 添加了STM32Cube扩展包支持通过JRE™捆绑支持
- 添加了安装过程的增强在STM32CubeMX主页上添加了关于新功能支持的可点击的新闻
- 在STM32L5系列中添加了对CMSIS包的支持

固件库版本更新：
- STM32F4 V1.26.0
- STM32G4 V1.4.0
- STM32H7 V1.9.0
- STM32L4 V1.17.0
- STM32L5 V1.4.0
- STM32WB V1.11.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/6a/a4/00/f1/ed/65/48/6a/stm32cubemx-win_v6-2-0/files/stm32cubemx-win_v6-2-0.zip/jcr:content/translations/en.stm32cubemx-win_v6-2-0.zip`

##### version 6.1.1
更新于2020年12月15日
主要更新日志：
- 修复X-CUBE-TOUCHFX的EWARM项目生成中断
- 修复波特率计算器问题

固件库版本更新：
- STM32F0 V1.11.2
- STM32F2 V1.9.2
- STM32F3 V1.11.2

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/0b/05/f0/25/c7/2b/42/9d/stm32cubemx_v6-1-1/files/stm32cubemx_v6-1-1.zip/jcr:content/translations/en.stm32cubemx_v6-1-1.zip`

##### version 6.1.0
更新于2020年11月13日
主要更新日志：
- 在STM32G0系列中添加了对新零件编号的支持：STM32G0B0CETx、STM32G0B0KETx、STM32G0B0RETx、STM32G0B0VETx、STM32G0B1C(C-E)Tx, STM32G0B1C(C-E)Ux, STM32G0B1K(C-E)Tx, STM32G0B1K(C-E)TxN, STM32G0B1K(C-E)Ux, STM32G0B1K(C-E)UxN, STM32G0B1M(C-E)Tx, STM32G0B1R(C-E)Ix, STM32G0B1R(C-E)Tx, STM32G0B1V(C-E)Ix, STM32G0B1V(C-E)Tx, STM32G0C1C(C-E)Tx, STM32G0C1C(C-E)Ux, STM32G0C1K(C-E)Tx, STM32G0C1K(C-E)TxN, STM32G0C1K(C-E)Ux, STM32G0C1K(C-E)UxN, STM32G0C1M(C-E)Tx, STM32G0C1R(C-E)Ix, STM32G0C1R(C-E)Tx, STM32G0C1V(C-E)Ix, STM32G0C1V(C-E)Tx
- 增加了对两个新STM32G0板的支持： NUCLEO-G0B1RE和STM32G0C1E-EV
- 增加了对STM32H7系列新零件编号的支持：STM32H735VGHx、STM32H725V（E-G）Hx
- 增加了对STM32L4系列新零件编号的支持：STM32L451CETx、STM32L452CETx和STM32L462CETx
- 增加了对STM32L0系列新零件编号的支持：STM32L073CZYx
- 添加了对STM32WL系列的支持：
- - 添加了对STM32WL系列中新零件编号的支持：STM32WL54CCUx、STM32WL54JCIx、STM32WL55CCUx、STM32WL55JCIx、STM32WL55UCYx、STM32WLE4C（8-B-C）Ux、STM32WLE4J（8-B-C）Ix、STM32WLE5C（8-B-C）Ux、STM32WLE5J（8-B）Yx
- - 添加了对两块板的支持：NUCLEO-WL55JC1和NUCLEO-WL55JC2-可以创建单核或双核项目。对于双核项目，可以将外围设备分配给Cortex®-M0+或Cortex®-M4核心
- 为STM32G0系列、STM32G4系列、STM32WB系列和STM32WL系列
- 增加了对STM32MP1系列新功能的LL支持：
- - USART智能卡模式
- - 通用异步收发设备RS-485模式
- - FMC PSRAM支持
- 增加了对一块新STM32MP1板的支持： STM32MP157F-DK2
- 增加了Zigbee®对STM32WB系列的支持：频道选择、端点选择、集群选择和分配以及集群回调管理
- 增加了中国大陆用户访问stmcu.com.cn视频教程的可能性
- 增加了视频教程功能的一些搜索增强增加了对双核STM32H7系列和STM32WL系列皮质®-M4的软件包支持
- 增加了示例选择器功能的一些增强
- 增加了对一个新的STM32L4板的支持： NUCLEO-L4A6ZG
- 在STM32CubeMX主页上对外部工具的新访问

固件库版本更新：
- STM32F0 V1.11.1
- STM32F1 V1.8.3
- STM32F2 V1.9.2
- STM32F3 V1.11.1
- STM32F4 V1.25.2
- STM32G0 V1.4.0
- STM32L0 V1.12.0
- STM32L1 V1.10.2
- STM32L5 V1.3.1
- STM32MP1 V1.3.0
- STM32WB V1.10.0
- 【新系列】STM32WL V1.0.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/70/b0/94/f1/df/17/44/c3/stm32cubemx_v6-1-0/files/stm32cubemx_v6-1-0.zip/jcr:content/translations/en.stm32cubemx_v6-1-0.zip`

##### version 6.0.1
更新于2020年8月11日
主要更新日志：
- 修复使用某些实用程序时意外删除项目数据
- 修复某些“非系统”IP的IRQ优先级在项目迁移后设置为最小值。
- 修复启用FreeRTOS™后，某些板无法启动。

固件库版本更新：
- STM32F0 V1.11.0
- STM32F1 V1.8.0
- STM32F2 V1.9.0
- STM32F3 V1.11.0
- STM32F4 V1.25.0
- STM32F7 V1.16.0
- STM32G0 V1.3.0
- STM32G4 V1.3.0
- STM32H7 V1.8.0
- STM32L0 V1.11.2
- STM32L1 V1.10.0
- STM32L4 V1.16.0
- STM32L5 V1.3.0
- STM32MP1 V1.2.0
- STM32WB V1.8.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/9e/ce/6e/18/d2/ff/46/57/stm32cubemx_v6-0-1/files/stm32cubemx_v6-0-1.zip/jcr:content/translations/en.stm32cubemx_v6-0-1.zip`

##### version 6.0.0
更新于2020年7月24日
主要更新日志：
- 在STM32G4系列中增加了对新零件编号的支持：STM32G491K（C-E）Ux、STM32G491C（C-E）Ux、STM32G491C（C-E）Tx、STM32G491REYx, STM32G491R(C-E)Tx, STM32G491R(C-E)Ix, STM32G491M(C-E)Sx, STM32G491M(C-E)Tx, STM32G491V(C-E)Tx, STM32G4A1KEUx, STM32G4A1CEUx, STM32G4A1CETx, STM32G4A1REYx, STM32G4A1RETx, STM32G4A1REIx, STM32G4A1MESx, STM32G4A1METx, and STM32G4A1VETx
- 在STM32H7系列中添加了对新零件编号的支持： STM32H723x、STM32H725x、STM32H730x、STM32H733x和STM32H735x
- 在STM32F4系列中添加了对一个新零件编号的支持：STM32F479IIHx
- 在STM32F7系列中添加了对三个新零件编号的支持：STM32F723V（C-E）Tx和STM32F733VETx
- 在STM32L0系列中添加了对新零件编号的支持：STM32L031C4Ux、STM32L041C6Ux、STM32L051C（6-8）Ux、STM32L052C（6-8）Ux、STM32L053C（6-8）Ux、STM32L062C8Ux、STM32L063C8Ux、STM32L071C8Ux、STM32L082KBUx和STM32L083RBTx
- 在STM32L1系列中添加了对新零件编号的支持：STM32L162QCHx、STM32L162VDYxX和STM32L162ZCTx
- 增加了对STM32L4系列新零件编号的支持：STM32L496VGTxP、STM32L496VGYxP和STM32L4A6VGTxP
- 增加了对STM32WB系列新零件编号的支持：STM32WB55VYYx
- 增加了对新板的支持：NUCLEO-G491RE、STM32H735G-DK、NUCLEO-H723ZG、NUCLEO-WB55RG、B-L462E-CELL1、B-L4S5I-IOT01和STM32MP157F-EV1
- 添加了视频教程功能来访问关于各种STM32CubeMX功能的视频教程
- 添加了示例选择器的支持，该选择器可以在多个参数之间进行示例过滤
- 添加了PCC对带SMPS的STM32L5xQ零件号的支持
- 软件包：
- - 用户界面增强，从引脚和配置视图简化对软件包安装和组件选择的访问，从组件选择器窗口简化对软件包留档的访问
- - 与Arm®CMSIS-Pack1.6.3版本一致的实施
- 添加了一个名为STM32PackCreator的图形工具，并在实用程序文件夹中与STM32CubeMX一起安装。它允许包开发人员创建为STM32CubeMX增强的软件包和STM32Cube扩展包。它可以从STM32CubeMX工具视图中的ST工具选项卡启动。

固件库版本更新：
STM32G4 V1.3.0
STM32H7 V1.8.0
STM32L1 V1.10.0
STM32L4 V1.16.0
STM32L5 V1.3.0
STM32WB V1.8.0

官网下载直链：`https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/92/11/23/cb/f0/12/40/95/stm32cubemx_v6-0-0/files/stm32cubemx_v6-0-0.zip/jcr:content/translations/en.stm32cubemx_v6-0-0.zip`





