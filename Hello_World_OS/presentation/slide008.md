           ______            _____                  _                ____             __            __           __                __                         _________ ____
          / ____/___  ____  / __(_)___ ___  _______(_)___  ____ _   / __ )____  _____/ /_  _____   / /_____     / /_  ____  ____  / /_   ____  __  _______   /  _/ ___// __ \
         / /   / __ \/ __ \/ /_/ / __ `/ / / / ___/ / __ \/ __ `/  / __  / __ \/ ___/ __ \/ ___/  / __/ __ \   / __ \/ __ \/ __ \/ __/  / __ \/ / / / ___/   / / \__ \/ / / /
        / /___/ /_/ / / / / __/ / /_/ / /_/ / /  / / / / / /_/ /  / /_/ / /_/ / /__/ / / (__  )  / /_/ /_/ /  / /_/ / /_/ / /_/ / /_   / /_/ / /_/ / /     _/ / ___/ / /_/ /
        \____/\____/_/ /_/_/ /_/\__, /\__,_/_/  /_/_/ /_/\__, /  /_____/\____/\___/_/ /_/____/   \__/\____/  /_.___/\____/\____/\__/   \____/\__,_/_/     /___//____/\____/
                               /____/                   /____/
        edit bochsrc.txt and add the below information:

        megs:            32
        romimage:        file=/full/path/to/bochs/BIOS-bochs-latest
        vgaromimage:     file=/full/path/to/bochs/VGABIOS-lgpl-latest
        ata0-master:     type=cdrom, path="/full/path/to/iso", status=inserted
        boot:            cdrom
        log:             bochslog.txt
        clock:           sync=realtime, time0=local
        cpu:             count=1, ips=1000000
















































































slide 008
