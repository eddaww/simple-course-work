package handler;

import com.google.gson.Gson;
import dao.BlockedUserDao;
import dto.BlockedUserDto;
import request.ParsedRequest;
import response.HttpResponseBuilder;
import response.RestApiAppResponse;

import java.util.List;

public class IsBlockedHandler implements BaseHandler {

    @Override
    public HttpResponseBuilder handleRequest(ParsedRequest request) {
        Gson gson = new Gson();
        BlockedUserDto blockedUserDto = gson.fromJson(request.getBody(), BlockedUserDto.class);
        boolean isBlocked = BlockedUserDao.getInstance().isBlocked(blockedUserDto.getBlocker(), blockedUserDto.getBlocked());

        RestApiAppResponse<BlockedUserDto> responseDto = new RestApiAppResponse<>(true, List.of(), String.valueOf(isBlocked));
        String responseBody = gson.toJson(responseDto);

        HttpResponseBuilder response = new HttpResponseBuilder();
        response.setStatus(StatusCodes.OK);
        response.setBody(responseBody);
        return response;
    }
}