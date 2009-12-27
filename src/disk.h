/**
 * Copyright (C) 2009, Shao Miller <shao.miller@yrdsb.edu.on.ca>.
 * Copyright 2006-2008, V.
 * For WinAoE contact information, see http://winaoe.org/
 *
 * This file is part of WinVBlock, derived from WinAoE.
 *
 * WinVBlock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WinVBlock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WinVBlock.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _DISK_H
#  define _DISK_H

/**
 * @file
 *
 * Disk specifics
 *
 */

enum DISK_DISKTYPE
{
  FloppyDisk,
  HardDisk,
  OpticalDisc
};

enum _disk__search_state
{
  SearchNIC,
  GetSize,
  GettingSize,
  GetGeometry,
  GettingGeometry,
  GetMaxSectorsPerPacket,
  GettingMaxSectorsPerPacket,
  Done
};
winvblock__def_enum ( disk__search_state );

winvblock__def_struct ( aoedisk_type )
{
  winvblock__uint32 MTU;
  winvblock__uint8 ClientMac[6];
  winvblock__uint8 ServerMac[6];
  winvblock__uint32 Major;
  winvblock__uint32 Minor;
  winvblock__uint32 MaxSectorsPerPacket;
  winvblock__uint32 Timeout;
};

winvblock__def_struct ( ramdisk_type )
{
  winvblock__uint32 DiskBuf;
  winvblock__uint32 DiskSize;
};

winvblock__def_struct ( disk__type )
{
  PDEVICE_OBJECT Parent;
  disk__type_ptr next_sibling_ptr;
  driver__dev_ext_ptr dev_ext_ptr;
  KEVENT SearchEvent;
  disk__search_state SearchState;
  KSPIN_LOCK SpinLock;
  winvblock__bool BootDrive;
  winvblock__bool Unmount;
  winvblock__uint32 DiskNumber;
  winvblock__bool IsRamdisk;
  winvblock__uint32 DiskType;
  winvblock__bool STDCALL (
  *Initialize
   ) (
  IN struct _driver__dev_ext * DeviceExtension
   );
  union
  {
    aoedisk_type AoE;
    ramdisk_type RAMDisk;
  };
  LONGLONG LBADiskSize;
  LONGLONG Cylinders;
  winvblock__uint32 Heads;
  winvblock__uint32 Sectors;
  winvblock__uint32 SectorSize;
  winvblock__uint32 SpecialFileCount;
};

extern irp__handling disk__handling_table[];
extern size_t disk__handling_table_size;

/*
 * Establish a pointer into the child disk device's extension space
 */
extern disk__type_ptr STDCALL get_disk_ptr (
  driver__dev_ext_ptr dev_ext_ptr
 );

#endif				/* _DISK_H */
