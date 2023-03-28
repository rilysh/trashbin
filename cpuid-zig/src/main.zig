const std = @import("std");

fn cpuid(
    leaf_id: u32,
    ebx: u32,
    ecx: u32,
    edx: u32
) u32 {
    return asm volatile (
        "cpuid"
        : [ret] "={eax}" (-> u32)
        : [leaf_id] "{eax}" (leaf_id),
        [ebx] "{ebx}" (ebx),
        [ecx] "{ecx}" (ecx),
        [edx] "{edx}" (edx)
        : "eax", "ebx", "ecx", "edx"
    );
}

pub fn main() !void {
    var regs:[4] u32 = undefined;
    var buf = [_]u8{undefined} ** 100;
    regs[0] = 1;
//    var r = cpuid(regs[0], regs[1], regs[2], regs[3]);

    var r = std.fmt.bufPrint(&buf, "{}", .{regs[1]});
    std.debug.print("{any}", .{r});
    std.debug.print("{s}", .{buf});
}